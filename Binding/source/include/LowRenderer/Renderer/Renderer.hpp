#pragma once
#include "LowRenderer/FrameBuffer/FrameBuffer.h"

class Scene;
class Shader;
class MeshRenderer;
class FrammeBuffer;



class Renderer
{
public:

	static inline FrameBuffer* OpenGlRenderToImgui = new FrameBuffer(800,800);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void RendereScene(Scene* scene, Shader* shader);

	Renderer();
	~Renderer();
private:
	void RenderMeshRender(const MeshRenderer* meshRender, Shader& shader, Scene* scene);
	void RenderStencil(const MeshRenderer* meshRender,const Shader& shader, Scene* scene);
};

