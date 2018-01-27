#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"

using namespace std;

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit()!= GLEW_OK){
    	cout<<"Error" <<endl;
    } else {
    	cout<<glGetString(GL_VERSION)<<endl;
    }

    {
		float positions[]={-0.5f,-0.5f, //0
							0.5f,-0.5f, //1
							0.5f,0.5f,  //2
							-0.5f,0.5f  //3
		};

		unsigned int indices[] ={
				0,1,2,
				2,3,0
		};

		VertexArray va;
		VertexBuffer vb(positions,4*2*sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb,layout);

		IndexBuffer ib(indices,6);
		Shader shader("res/shaders/basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		Renderer renderer;

		float r = 0.0f;
		float increment = 0.05f;
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();
			shader.Bind();
			shader.SetUniform4f("u_Color",  r, 0.3f, 0.8f, 1.0f);

			renderer.Draw(va,ib,shader);
			if (r> 1.0f)
				increment = -0.05f;
			else if (r< 0.0f)
				increment = 0.05f;

			r +=increment;

			GLCall(glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, nullptr));


			/* Swap front and back buffers */
			GLCall(glfwSwapBuffers(window));

			/* Poll for and process events */
			GLCall(glfwPollEvents());
		}

	}

    glfwTerminate();
    return 0;
}
