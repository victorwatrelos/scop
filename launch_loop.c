#include "init_opengl.h"


void	launch_loop(t_opengl *opengl)
{
	float	alpha;

	alpha = 0.f;
	while (!glfwWindowShouldClose (opengl->window))
	{
		opengl->rot_matrix = get_rot_matrix(alpha);
		glUniformMatrix4fv(opengl->uloc_R, 1, GL_FALSE, opengl->rot_matrix);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram (opengl->shader_program);
		glBindVertexArray (opengl->vao);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glfwPollEvents ();
		glfwSwapBuffers (opengl->window);
		alpha += 0.05f;
		if (alpha > 2 * M_PI)
			alpha -= 2 * M_PI;
	}
	glDeleteShader(opengl->fs);
	glDeleteShader(opengl->vs);
}
