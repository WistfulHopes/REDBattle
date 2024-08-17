#include "RaylibDraw.h"

#include "rlgl.h"

void DrawTexturePlane(const Texture2D& texture, Vector3 pos, Vector2 size, Vector2 texCoords[4], Color color)
{
    rlSetTexture(texture.id);
    
    rlPushMatrix();
    rlTranslatef(pos.x, pos.y, pos.z);
    rlScalef(size.x, size.y, 1);

    rlBegin(RL_QUADS);
    rlColor4ub(color.r, color.g, color.b, color.a);
    rlNormal3f(0.0f, 1.0f, 0.0f);

    rlTexCoord2f(texCoords[0].x, texCoords[0].y);
    rlVertex3f(-0.5f, 0.0f, 0.f);
    rlTexCoord2f(texCoords[1].x, texCoords[1].y);
    rlVertex3f(-0.5f, 1.0f, 0.0f);
    rlTexCoord2f(texCoords[2].x, texCoords[2].y);
    rlVertex3f(0.5f, 1.0f, 0.0f);
    rlTexCoord2f(texCoords[3].x, texCoords[3].y);
    rlVertex3f(0.5f, 0.0f, 0.0f);
    rlEnd();
    rlSetTexture(0);
    rlPopMatrix();
}
