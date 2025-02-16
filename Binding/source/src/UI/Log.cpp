#include "UI/Log.hpp"
#include<Core/Debug/Imgui/imgui_impl_glfw.h>
#include<Core/Debug/Imgui/imgui_impl_opengl3.h>
#include <Core/Debug/Imgui/imgui_internal.h>


void Log::UpdateLayer(Project& currentProject, std::vector<InputEvent*>& inputsEvents)
{
    
  /*
    if (!ImGui::Begin(WindowName.c_str(), &Isopen))
    {
      //  ImGui::End();
        return;
    }*/
 
    ImGui::Begin(WindowName.c_str(), &Isopen);
   
    static bool d = true;
    ImGui::ShowDemoWindow(&d);

       if (ImGui::BeginPopup("Options"))
       {
           ImGui::Checkbox("Auto-scroll", &AutoScroll);
           ImGui::EndPopup();
       }

       ImGui::Text( std::to_string(ImGui::GetIO().Framerate).c_str());

   ImGui::End();
    
}

void Log::ListenToInput(Project& currentProject,std::vector<InputEvent*>& inputEvent)
{
}
