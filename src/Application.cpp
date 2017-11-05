#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include <fstream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;

struct ShaderProgramSource{
	std::string VertexSource;
	std::string FragmentSource;
};

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

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit()!= GLEW_OK){
    	cout<<"Error" <<endl;
    } else {
    	cout<<glGetString(GL_VERSION)<<endl;
    }

    float positions[]={-0.5f,-0.5f, //0
    				 	0.5f,-0.5f, //1
						0.5f,0.5f,  //2
						-0.5f,0.5f  //3
    };

    unsigned int indices[] ={
    		0,1,2,
			2,3,0
    };

    unsigned int buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER,6*2*sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, sizeof(float)*2,0);


    unsigned int ibo;
	glGenBuffers(1,&ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,6*sizeof(unsigned int), indices, GL_STATIC_DRAW);

    ShaderProgramSource source = parseShader("res/shaders/basic.shader");
    cout<<"VERTEX" <<endl;
    cout<< source.VertexSource <<endl;
    cout<<"FRAGMENT" << endl;
    cout<<source.FragmentSource<<endl;

    glBindBuffer(GL_ARRAY_BUFFER,0);



    unsigned int shader = createShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, nullptr);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
