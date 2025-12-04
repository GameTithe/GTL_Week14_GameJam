#pragma once


#include "SkinnedMeshComponent.h"
#include "NvCloth/include/Factory.h"
#include "NvCloth/include/Fabric.h"
#include "NvCloth/include/Cloth.h"
#include "NvCloth/include/Solver.h"
#include "NvCloth/include/Callbacks.h"	
#include "NvCloth/include/NvClothExt/ClothFabricCooker.h"
#include "foundation/PxAllocatorCallback.h"
#include "foundation/PxErrorCallback.h"
#include "UClothComponent.generated.h"

class UClothComponent : public USkinnedMeshComponent
{
	GENERATED_REFLECTION_BODY()
public:
	UClothComponent();
	virtual ~UClothComponent();

	// Lifecycle
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime) override;
	virtual void OnCreatePhysicsState() override;
	virtual void CollectMeshBatches(TArray<FMeshBatchElement>& OutMeshBatchElements, const FSceneView* View) override;
	
	// Cloth Set up
	void SetupClothFromMesh();
	void ReleaseCloth();

	// Helper functions
	int32 GetBoneIndex(const FName& BoneName) const;
	FTransform GetBoneTransform(int32 BoneIndex) const;
	FVector GetBoneLocation(const FName& BoneName);
	FVector GetAttachmentPosition(int32 AttachmentIndex);

	// Cloth Pain API 
	/*
		int32 GetClothVertexCount() const { return ClothParticles.Num(); }
		FVector GetClothVertexPosition(int32 ClothVertexIndex) const;
		float GetVertexWeight(int32 ClothVertexIndex) const;
		void SetVertexWeight(int32 ClothVertexIndex, float Weight);
		void SetVertexWeightByMeshVertex(uint32 MeshVertexIndex, float Weight);
		void InitializeVertexWeights();
		void ApplyPaintedWeights();
		void LoadWeightsFromPhysicsAsset(const TMap<uint32, float>& InClothVertexWeights);  // PhysicsAsset에서 weight 로드
		const TArray<float>& GetVertexWeights() const { return ClothVertexWeights; }
		const TArray<uint32>& GetClothVertexToMeshVertexMapping() const { return ClothVertexToMeshVertex; }
		int32 FindClothVertexByMeshVertex(uint32 MeshVertexIndex) const; 
	*/

protected:
	// Internal helper
	void CreateClothFabric();
	void CreateClothInstance();
	void CreatePhaseConfig(); 
	void CreateSolver();

	// Cloth Data
	TArray<physx::PxVec4> ClothParticles;
	TArray<physx::PxVec4> PreviousParticles;
	TArray<physx::PxVec3> ClothNormals;
	TArray<uint32> ClothIndices;                 
	TArray<float> ClothInvMasses;               

	// Cloth Paint 

	// Attachment Data
	
	// Constraints
};