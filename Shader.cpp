#include "Shader.h"

#include <glad/glad.h>

#include "ShaderSource.h"

Shader::Shader() {
	// Generate shaders
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Set shader sources
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);

	// Compile shaders without checking for errors because yolo
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	// Generate program
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	// We can destroy the shaders now that we have a program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Get the location of the uniforms
	matrixLocation = glGetUniformLocation(programID, "u_modelViewProjectionMatrix");
	offsetLocation = glGetUniformLocation(programID, "u_xOffset");
}

void Shader::start() {
	// Bind this shader for rendering
	glUseProgram(programID);
}

void Shader::stop() {
	// Unbind shader, usually not necessary
	glUseProgram(0);
}

void Shader::uploadMatrix(float* matrix) {
	// Upload modelViewProjection matrix
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);
}

void Shader::uploadOffset(float offset) {
	// Upload offset
	glUniform1f(offsetLocation, offset);
}

void Shader::cleanUp() {
	// Delete the program
	glDeleteProgram(programID);
}