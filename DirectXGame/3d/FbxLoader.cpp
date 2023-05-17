#include "FbxLoader.h"
#include <cassert>

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
const std::string FbxLoader::baseDirectory = "Resources/";

FbxLoader* FbxLoader::GetInstance()
{
	static FbxLoader instance;
	return &instance;
}

void FbxLoader::Initialize(ID3D12Device* device)
{
	// 再初期化チェック
	assert(fbxManager_ == nullptr);
	// 引数からメンバ変数に代入
	this->device_ = device;
	// FBXマネージャの生成
	fbxManager_ = FbxManager::Create();
	// FBXマネージャの入出力設定
	FbxIOSettings* ios = FbxIOSettings::Create(fbxManager_, IOSROOT);
	fbxManager_->SetIOSettings(ios);
	// FBXインポータの生成
	fbxImporter_ = FbxImporter::Create(fbxManager_, "");
}

void FbxLoader::Finalize()
{
	// 各FBXインスタンスの破棄
	fbxImporter_->Destroy();
	fbxManager_->Destroy();
}

void FbxLoader::LoadModelFromFile(const string& modelName)
{
	// モデルと同じ名前のフォルダから読み込む
	const string directryPath = baseDirectory + modelName + "/";
	// 拡張子.fbxを付加
	const string fileName = modelName + ".fbx";
	// 連結してフルパスを得る
	const string fullpath = directryPath + fileName;

	// ファイル名を指定してFBXファイルを読み込む
	if (!fbxImporter_->Initialize(fullpath.c_str(),
		-1, fbxManager_->GetIOSettings()))
	{
		assert(0);
	}
	// シーン生成
	FbxScene* fbxScene = FbxScene::Create(fbxManager_, "fbxScene");

	// ファイルからロードしたFBXの情報をシーンにインポート
	fbxImporter_->Import(fbxScene);
}
