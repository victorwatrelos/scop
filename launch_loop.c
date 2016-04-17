#include "init_opengl.h"


void	launch_loop(t_opengl *opengl)
{
	while (!glfwWindowShouldClose (opengl->window))
	{
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram (opengl->shader_program);
		glBindVertexArray (opengl->vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays (GL_TRIANGLES, 0, 36);
		// update other events like input handling 
		glfwPollEvents ();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers (opengl->window);
	}
	glDeleteShader(opengl->fs);
	glDeleteShader(opengl->vs);

}
