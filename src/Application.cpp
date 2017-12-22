#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

using namespace std;

static ShaderProgramSource parseShader (const std::string& filepath){
	std::ifstream stream (filepath);

	enum class ShaderType{
		NONE = -1, VERTEX =0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type =  ShaderType::NONE;

	while(getline(stream, line)){
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos){
				type = ShaderType::VERTEX;

			}
			else if (line.find("fragment") != std::string::npos) {
				type= ShaderType::FRAGMENT;
			}
		} else {
			ss[static_cast<int>(type)] << line << '\n';
		}

	}
	return {ss[0].str(), ss[1].str()};
}

static unsigned int compileShader (unsigned int type, const std::string& source){
	 unsigned int id = glCreateShader(type);
	 const char *src = source.c_str();
	 glShaderSource(id,1,&src,nullptr);
	 glCompileShader(id);

	 int result;
	 glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	 if (result == GL_FALSE){
		 int length;
		 glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		 char message[length];
		 glGetShaderInfoLog(id, length, &length,message);
		 cout<<"Failed to compile" << (type==GL_VERTEX_SHADER ? "vertex" : "fragment") <<"shader"<<endl;
		 cout<<message<<endl;
		 glDeleteShader(id);
		 return 0;
	 }

	 return id;
}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader){
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER,vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER,fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

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

		ShaderProgramSource source = parseShader("res/shaders/basic.shader");
		cout<<"VERTEX" <<endl;
		cout<< source.VertexSource <<endl;
		cout<<"FRAGMENT" << endl;
		cout<<source.FragmentSource<<endl;

		GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));



		unsigned int shader = createShader(source.VertexSource, source.FragmentSource);
		GLCall(glUseProgram(shader));

		GLCall(int location = glGetUniformLocation(shader, "u_Color"));
		ASSERT(location != -1 );
		GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));
		/* Loop until the user closes the window */

		va.Unbind();
		GLCall(glUseProgram(0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		float r = 0.0f;
		float increment = 0.05f;
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			GLCall(glUseProgram(shader));
			GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

			va.Bind();
			ib.Bind();


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

		glDeleteProgram(shader);
	}

    glfwTerminate();
    return 0;
}
