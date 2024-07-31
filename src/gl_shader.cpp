#include <iostream>
#include <string>

// OpenGL
#include "gl/glew.h"
#include "gl_shader.h"

#include "e_filesys.h"

using namespace std;

void Shader::compile(const GLchar* vertdata, const GLchar* fragdata)
{
	GLuint vertexshader, fragmentshader;
	GLint success = true;
	GLchar log[512];

	//
	// VERTEX SHADER
	//

	try
	{
		string source = readFile(vertdata);

		const char* c_source = source.c_str();

		vertexshader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexshader, 1, &c_source, nullptr);
		glCompileShader(vertexshader);


		glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexshader, 512, nullptr, log);
			cerr << "Vertex shader couldn't be compiled | " << source << endl << log << endl;
			exit(1);
		}
	}
	catch (exception e)
	{
		cerr << "Vertex Shader couldn't be loaded" << endl;
		exit(1);
	}

	//
	// FRAGMENT SHADER
	//

	try
	{
		string source = readFile(fragdata);

		const char* c_source = source.c_str();

		fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentshader, 1, &c_source, nullptr);
		glCompileShader(fragmentshader);


		glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentshader, 512, nullptr, log);
			cerr << "Fragment shader couldn't be compiled | " << source << endl << log << endl;
			exit(1);
		}
	}
	catch (exception e)
	{
		cerr << "Fragment Shader couldn't be loaded" << endl;
		exit(1);
	}

	id_ = glCreateProgram();
	glAttachShader(id_, vertexshader);
	glAttachShader(id_, fragmentshader);
	glLinkProgram(id_);

	glGetProgramiv(id_, GL_LINK_STATUS, & success);
	if (!success)
	{
		glGetProgramInfoLog(id_, 512, nullptr, log);
		cerr << "Program linking error" << endl << log << endl;
		exit(1);
	}

	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
}

void Shader::activate()
{
	glUseProgram(id_);
}

void Shader::setBool(const GLchar* name, GLboolean value)
{
	glUniform1i(glGetUniformLocation(id_, name), value);
}

void Shader::setInt(const GLchar* name, GLint value)
{
	glUniform1i(glGetUniformLocation(id_, name), value);
}

void Shader::setFloat(const GLchar* name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(id_, name), value);
}

void Shader::setVec2f(const GLchar* name, GLfloat x, GLfloat y)
{
	glUniform2f(glGetUniformLocation(id_, name), x, y);
}

void Shader::setVec3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(glGetUniformLocation(id_, name), x, y, z);
}

void Shader::setVec4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat a)
{
	glUniform4f(glGetUniformLocation(id_, name), x, y, z, a);
}