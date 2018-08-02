#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	m_objContainer = NULL;
	m_deviceContext = NULL;
	m_device = NULL;
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::Initialize(ID3D11DeviceContext* deviceContext, ID3D11Device* device, float width, float height, Input* input)
{
	m_objContainer = new std::vector<GameObject*>();

	m_deviceContext = deviceContext;
	m_device = device;
	m_scrWidth = width;
	m_scrHeight = height;
	m_input = input;

	FirstCreate();
}

void ObjectManager::FirstCreate()
{
	CreateObject(200, 200, SPRITE_INFO{SEAFLOOR, 100.0f, 100.0f});
	//CreateObject(400, 400, SPRITE_INFO{SEAFLOOR, 100.0f, 100.0f });
	//CreateObject(600, 600, SPRITE_INFO{ SEAFLOOR, 100.0f, 100.0f });
}

void ObjectManager::InsertObject()
{

}

void ObjectManager::CreateObject(float posX, float posY, SPRITE_INFO spriteInfo)
{
	Player *temp = new Player();
	temp->Initialize(m_deviceContext, m_device, posX, posY, spriteInfo, m_scrWidth, m_scrHeight, m_input);
	m_objContainer->push_back(temp);

	/*GameObject *temp = new GameObject();
	temp->Initialize(m_deviceContext, m_device, posX, posY, spriteInfo, m_scrWidth, m_scrHeight);
	m_objContainer->push_back(temp);*/
}

void ObjectManager::Render()
{
	for (iter = m_objContainer->begin(); iter != m_objContainer->end(); ++iter)
	{
		(*iter)->Render(m_deviceContext);
		ID3D11ShaderResourceView* temp = (*iter)->GetTextureView();
		m_deviceContext->PSSetShaderResources(0, 1, &temp);
		m_deviceContext->DrawIndexed((*iter)->GetSprite()->GetIndex(), 0, 0);
	}
}

void ObjectManager::Release()
{

}