// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomGeometryScriptBPLibrary.h"
#include "CustomGeometryScript.h"
#include "DynamicMesh/DynamicMesh3.h"
#include "DynamicMesh/MeshNormals.h"

using namespace UE::Geometry;

UCustomGeometryScriptBPLibrary::UCustomGeometryScriptBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UCustomGeometryScriptBPLibrary::CustomGeometryScriptSampleFunction(float Param)
{
	return -1;
}

UDynamicMesh* UCustomGeometryScriptBPLibrary::ExplodeMesh(UDynamicMesh* TargetMesh, float Distance)
{
	if (TargetMesh == nullptr)
	{
		return TargetMesh;
	}

	FRandomStream Random(31337);

	TargetMesh->EditMesh([&](FDynamicMesh3& EditMesh)
	{
			for (int32 vertexId : EditMesh.VertexIndicesItr())
			{
				FVector3d vertexPos = EditMesh.GetVertex(vertexId);
				FVector3d Normal = FMeshNormals::ComputeVertexNormal(EditMesh, vertexId);
				
				double Offset = Distance * (double)Random.GetFraction() - (Distance, 2.0f); 
				vertexPos += Offset * Normal;

				EditMesh.SetVertex(vertexId, vertexPos);
			}
	});

	return TargetMesh;
}