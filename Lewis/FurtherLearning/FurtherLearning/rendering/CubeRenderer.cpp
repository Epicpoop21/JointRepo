#include "CubeRenderer.h"

CubeRenderer::CubeRenderer() : chunk(std::make_unique<Chunk>())
{
	
}

CubeRenderer::~CubeRenderer()
{

}

void CubeRenderer::Render()
{
	chunk->RenderChunk();
}


