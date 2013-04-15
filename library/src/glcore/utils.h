#pragma once

namespace gel
{
	template<GLenum U> void Bind(GLenum target, cGlid<typename U> obj) {}
	template<GLenum U> void Bind(cGlid<typename U> obj) {}

	// Bind calls w/ target
	template<> void Bind(GLenum target, cGlid<GL_BUFFER> obj)
	{ glBindBuffer(target,obj.Id()); }

	template<> void Bind(GLenum target, cGlid<GL_TEXTURE> obj)
	{ glBindTexture(target,obj.Id()); }


	// Bind calls no target
	template<> void Bind(cGlid<GL_VERTEX_ARRAY> obj)
	{ glBindVertexARray(obj.Id()); }


}