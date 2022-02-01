#include "camera.h"

Camera initCamera()
{
	Camera camera;

	glm_vec2_zero(camera.pos);

	glm_ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f, camera.proj);

	glm_mat4_identity(camera.view);

	return camera;
}

void sendViewProjMat(Camera camera)
{
	glUniformMatrix4fv(camera.projLoc, 1, GL_FALSE, camera.proj[0]);

	glm_mat4_identity(camera.view);

	glm_translate_x(camera.view, -camera.pos[0]);
	glm_translate_y(camera.view, -camera.pos[1]);

	glUniformMatrix4fv(camera.viewLoc, 1, GL_FALSE, camera.view[0]);
}
