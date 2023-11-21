#ifndef PREFABS_H_
#define PREFABS_H_

#include <memory>
#include <ShaderDataTypes.h>
#include <Shader.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <GeometricTools.h>

namespace Prefabs
{
	std::shared_ptr<VertexArray> MakeBoard()
	{
		auto varr = std::make_shared<VertexArray>();

		// board vertex data
		auto bv = GeometricTools::UnitGridGeometry2DWTCoords<8, 8>();
		auto vbuff = std::make_shared<VertexBuffer>(bv.data(), bv.size() * sizeof(float));
		vbuff->SetLayout({
			{ShaderDataType::Float2, "positions"},
			{ShaderDataType::Float2, "tex_coords"}
			});

		// board indices
		auto iv = GeometricTools::UnitGridTopologyTriangles(8, 8);
		auto ibuff = std::make_shared<IndexBuffer>(iv.data(), iv.size());

		varr->AddVertexBuffer(vbuff);
		varr->SetIndexBuffer(ibuff);

		return varr;
	}

	std::shared_ptr<VertexArray> MakeCube()
	{
		auto varr = std::make_shared<VertexArray>();

		// board vertex data
		auto bv = GeometricTools::UnitCubePositions();
		auto vbuff = std::make_shared<VertexBuffer>(bv.data(), bv.size() * sizeof(float));
		vbuff->SetLayout({ {ShaderDataType::Float3, "position"} });

		// board indices
		auto iv = GeometricTools::UnitCubeIndices();
		auto ibuff = std::make_shared<IndexBuffer>(iv.data(), iv.size());

		varr->AddVertexBuffer(vbuff);
		varr->SetIndexBuffer(ibuff);

		return varr;
	}
}

#endif // !PREFABS_H_
