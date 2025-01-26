
#pragma once

#include "./camera.hpp"
#include <glm/gtc/type_ptr.hpp>

class Renderer {

	private:

		GLuint m_prog;
		GLuint m_vbo;
		GLuint m_vao;
		
		Camera camera;
		glm::mat4 projection;
	private:

		GLuint compileShader(GLenum type, const char* source) {

			// create shader object
			GLuint shader = glCreateShader(type);
			glShaderSource(shader, 1, &source, nullptr);
			glCompileShader(shader);

			// error checking
			GLint compiled = GL_FALSE;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

			// if the shader is not compiled something went wrong
			if (compiled == GL_FALSE) {
				GLint length = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

				std::vector<char> error (length);
				glGetShaderInfoLog(shader, length, &length, error.data());

				printf("Shader module compilation failed with error: %s\n", error.data());
			}

			return shader;
		}

		GLuint linkShaders(GLuint vertex, GLuint fragment) {

			// create shader program
			GLuint program = glCreateProgram();
			glAttachShader(program, vertex);
			glAttachShader(program, fragment);
			glLinkProgram(program);

			// error checking
			GLint linked = GL_FALSE;
			glGetProgramiv(program, GL_LINK_STATUS, &linked);

			// if the program is not linked something went wrong
			if(linked == GL_FALSE) {
				GLint length = 0;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

				std::vector<char> error (length);
				glGetProgramInfoLog(program, length, &length, error.data());

				printf("Shader program linking failed with error: %s\n", error.data());
			}

			return program;

		}

		void addVertexAttribute(const char* name, int count, int stride, long offset) {

			// get the "handle" (also called 'location' or 'index') of the vertex shader input variable
			GLint location = glGetAttribLocation(this->m_prog, name);

			// add the currently bound VBO to the currently bound VAO as a source for the data in vertex attribute 'name'
			glVertexAttribPointer(location, count, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*) (offset * sizeof(float)));

			// enable the attribute, otherwise it would have been ignored during rendering
			glEnableVertexAttribArray(location);
		}

	private:

		void initShaders() {

			const char* vertex_source = R"(
				#version 330 core

				layout(location = 0) in vec2 iPos;
				layout(location = 1) in vec3 iColor;

				uniform mat4 uView;
				uniform mat4 uProjection;

				out vec3 vColor;

				void main() {
					gl_Position = uProjection * uView * vec4(iPos, -1.0, 1.0);
					vColor = iColor;
				})";

			const char* fragment_source = R"(
				#version 330 core

				in vec3 vColor;

				out vec4 fColor;

				void main() {
					fColor = vec4(vColor, 1);
				}
			)";


			GLuint vert = compileShader(GL_VERTEX_SHADER, vertex_source);
			GLuint frag = compileShader(GL_FRAGMENT_SHADER, fragment_source);

			this->m_prog = linkShaders(vert, frag);

			// Shaders can now be deleted
			glDeleteShader(vert);
			glDeleteShader(frag);

			// make all future rendering calls use this shader program
			glUseProgram(this->m_prog);
		}

		void initVertexBuffer() {

			const GLfloat vertices[] = {
			//	  X      Y      R      G      B
				-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
				 1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
				 1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
				 -1.0f,  1.0f,  0.3f,  0.3f,  0.3f,
				 -1.0f, -1.0f,  0.6f,  0.6f,  0.6f,
				 1.0f,  1.0f,  0.9f,  0.9f,  0.9f,
			};

			GLuint vbo;

			// create one new buffer, at this point no actual buffer memory is reserved, the handle is written to the given pointer
			glGenBuffers(1, &vbo);

			// make all future GL_ARRAY_BUFFER operations refere to this VBO
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			// upload triangle mesh to the GPU to the GL_ARRAY_BUFFER buffer, at this point buffer is allocated in VRAM
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			// save handle so we can delete the buffer later
			this->m_vbo = vbo;

		}

		void initVertexArray() {

			GLuint vao;

			// same as with VBO create one new handle
			glGenVertexArrays(1, &vao);

			// make all future VAO operations refer to this VAO
			glBindVertexArray(vao);

			// length=2, total=5, offset=0
			addVertexAttribute("iPos", 2, 5, 0);

			// length=3, total=5, offset=2
			addVertexAttribute("iColor", 3, 5, 2);

			// save handle so we can delete the VAO later
			this->m_vao = vao;

		}

	public:

		Renderer() {
			initShaders();
			initVertexBuffer();
			initVertexArray();

			// set fixed-function back buffer clear color, 4th value is used as the clear value for the depth buffer
			glClearColor(0.0, 0.0, 0.0, 1.0);
		}

		Renderer(int width, int height) {
			initShaders();
			initVertexBuffer();
			initVertexArray();

			// set fixed-function back buffer clear color, 4th value is used as the clear value for the depth buffer
			glClearColor(0.0, 0.0, 0.0, 1.0);

			projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
		}

		// draw our triangle to the back buffer
		void draw() {

			// clear the back buffer
			glClear(GL_COLOR_BUFFER_BIT);


			GLuint viewLoc = glGetUniformLocation(m_prog, "uView");
			GLuint projLoc = glGetUniformLocation(m_prog, "uProjection");

			if (viewLoc == -1) {
				printf("Error: uView not found in shader!\n");
			}
			
			if (projLoc == -1) {
				printf("Error: uProjection not found in shader!\n");
			}
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

			// draw 3 points based on the current settings and bound VAO and Program, the currently bound VBO is irrelevant
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		// perform cleanup, frees all resources
		void close() {
			glDeleteProgram(this->m_prog);
			glDeleteBuffers(1, &this->m_vbo);
			glDeleteVertexArrays(1, &this->m_vao);
		}


		Camera& getCamera()
		{
			return camera;
		}


};
