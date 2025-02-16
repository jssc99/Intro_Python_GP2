#include <Ressources/Shader/Shader.h>
#include "Ressources/RessourcesManager/RessourcesManager.h"

#include "Core/Debug/LogClass.h"










void Shader::Use()
{
    glUseProgram(m_ID);
}


void Shader::Use() const
{
    glUseProgram(m_ID);
}

void Shader::UnUse() const
{
    glUseProgram(0);
}
void Shader::UnUse()
{
    glUseProgram(0);
}

void Shader::SetBool(const std::string& name, bool value) const
{
    int currentLoc = GetUnitform(name.c_str());
    glUniform1i(currentLoc, (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
    int currentLoc = GetUnitform(name.c_str());

    glUniform1i(currentLoc, value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    int currentLoc = GetUnitform(name.c_str());

    glUniform1f(currentLoc, value);

}

void Shader::SetVector4(const std::string& name, const float* value) const
{


    int currentLoc = GetUnitform(name.c_str());
    glUniform4fv(currentLoc, 1, value);
}

void Shader::SetMatrix(const std::string& name, const float* matrixValue) const
{

    int currentLoc = GetUnitform(name.c_str());
    glUniformMatrix4fv(currentLoc, 1, GL_FALSE, matrixValue);
}

void Shader::SetVector3(const std::string& name, const float* value) const
{
    int currentLoc = GetUnitform(name.c_str());

    glUniform3fv(currentLoc, 1, value);
}

void Shader::SetMaterial(const std::string& name, const Material& material) const
{
  

}

GLuint Shader::GetId() const
{
    return m_ID;
}

void Shader::InitResource()
{
    // 2. compile shaders
    unsigned int vertex, fragment, geometry;
    int success;
    char infoLog[512];

    bool HasGeomtryShader = shaderFlag & SHADERFLAG::GEOMETRY;

    const char* vertexShader = m_vShaderCode.c_str();
    const char* gertexShader = m_gShaderCode.c_str();
    const char* fertexShader = m_fShaderCode.c_str();


    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShader, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        LOG(mShaderName + " : ERROR::SHADER::VERTEX::COMPILATION_FAILED" + '\n' + std::to_string(*infoLog), STATELOG::WARNING);
    }
    else
    {
        LOG(mShaderName + " : VERTEX::PROGRAM::COMPILATION_SUCCED", STATELOG::GOOD);

    }


    if(HasGeomtryShader)
    {
        // geometry Shader
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gertexShader, NULL);
        glCompileShader(geometry);
        // print compile errors if any
        glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(geometry, 512, NULL, infoLog);
            LOG(mShaderName + " : ERROR::SHADER::GEOMETRY::COMPILATION_FAILED" + '\n' + std::to_string(*infoLog), STATELOG::WARNING);
        }
        else
        {
            LOG(mShaderName + " : GEOMETRY::PROGRAM::COMPILATION_SUCCED", STATELOG::GOOD);

        }
    }
   




    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fertexShader, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        LOG(mShaderName + " :ERROR::SHADER::FRAG::COMPILATION_FAILED" + '\n' + std::to_string(*infoLog), STATELOG::WARNING);
    }
    else
    {
        LOG(mShaderName + " : FRAG::PROGRAM::COMPILATION_SUCCED" + mShaderName, STATELOG::GOOD);

    }


    // shader Program
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);

    if (HasGeomtryShader)
    {
        glAttachShader(m_ID, geometry);
    }
  // 
    glLinkProgram(m_ID);
    // print linking errors if any
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        LOG(mShaderName + "ERROR::SHADER::PROGRAM::LINKING_FAILED" + std::to_string(*infoLog), STATELOG::WARNING);
    }
    else
    {
        LOG(mShaderName + " : SHADER::PROGRAM::LINKED", STATELOG::GOOD);

    }



    // delete Shader cause we liked them before so there no longer nessecery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(HasGeomtryShader)
    {
        glDeleteShader(geometry);
    }

}






Shader::Shader(const fs::path& FilePath)
{
    SHADERFLAG flag = GetShaderFlagsInDirectory(FilePath,*this);
}

SHADERFLAG Shader::GetShaderFlagsInDirectory(const fs::path& FilePath, Shader& shader)
{
    using RES = ResourcesManager;
    SHADERFLAG flag = NONE;

    shader.mShaderName = FilePath.filename().generic_string();

    for (const auto& entry : fs::directory_iterator(FilePath))
    {
        if (RES::IsThisValidForThisFormat(entry.path().string(), RES::GetVertexShaderFormat()))
        {
            flag << VERTEX;
            Shader::LoadShaderFileInString(shader.m_vShaderCode, entry);
        }

        if (RES::IsThisValidForThisFormat(entry.path().string(), RES::GetFragmentShaderFormat()))
        {
            flag << FRAGMENT;
            Shader::LoadShaderFileInString(shader.m_fShaderCode, entry);

        }
        if (RES::IsThisValidForThisFormat(entry.path().string(), RES::GetGeometryShaderFormat()))
        {
            flag << GEOMETRY;
            Shader::LoadShaderFileInString(shader.m_gShaderCode, entry);
        }

    }

    return flag;
}

Shader::~Shader()
{
    if(glIsShader(m_ID))
    {
        glDeleteShader(m_ID);
    }
}

GLint Shader::GetUnitform(const std::string& name) const
{

    if (m_UniformMap.find(name) != m_UniformMap.end())
    {
        return m_UniformMap[name];
    }

    GLint location = glGetUniformLocation(m_ID, name.c_str());
    m_UniformMap[name] = location;

    return location;
}

void Shader::LoadShaderFileInString(std::string& string, const fs::path& FilePath)
{
    std::string code;
    std::ifstream vShaderFile;
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // open files
        vShaderFile.open(FilePath);

        std::stringstream stream;
        // read file's buffer contents into streams
        stream << vShaderFile.rdbuf();

        // close file handlers
        vShaderFile.close();
        // convert stream into string
        code = stream.str();
    }
    catch (std::ifstream::failure e)
    {

        LOG(" :  ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ \n ", STATELOG::WARNING);
    }
    string = code;
}

