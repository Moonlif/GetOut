#pragma once
#include "cFloor.h"
#include "cWall.h"
#include "cCeiling.h"
#include "cSurface.h"
#include "cObjLoader.h"
#include "cMapObject.h"
#include "cObjectSurface.h"

class cMap
{
private:
	cFloor*			m_pFloor;
	cSurface*		m_pSurface;
	cWall*			m_pWall;
	cCeiling*		m_pCeiling;
	cObjectSurface* m_pObjSurface;


	//::vector<cMapObject*> vecMapObj;
	cMapObject* m_pObjShackles;
	cMapObject* m_pObjPrisonbar;
	cMapObject* m_pObjPrisonbarRow;
	cMapObject* m_pObjShelf;
	cMapObject* m_pObjBox;
	cMapObject* m_pObjWinebarrel;
	cMapObject* m_pObjShelfHigh;
	cMapObject* m_pObjPiano;
	cMapObject* m_pObjBed;

	cMapObject* m_pObjDesk;
	//cMapObject* m_pObjTable;
	cMapObject* m_pObjSofa;
	cMapObject* m_pObjChair;
	cMapObject* m_pObjBarrel;
	cMapObject* m_pDrawers;
	cMapObject* m_pIronmaiden;
	cMapObject* m_pTorture;
	cMapObject* m_pStonetable;
	cMapObject* m_pBookPile1;
	cMapObject* m_pBookRow;
	
public:
	cMap();
	~cMap();
	void Setup();
	void SetupObject();
	void Render();
	void RenderObject();
	cSurface* getSurface() { return m_pSurface; };
	cObjectSurface* getObjSurface(){ return m_pObjSurface; };
	bool GetSurfaceHeight(IN float x, OUT float & y, IN float z);
	bool GetObjectSurface(IN float x, OUT float & y, IN float z);
	bool GetPassSurface(IN float x, OUT float & y, IN float z);
	bool GetMovePossible(IN float x, OUT float & y, IN float z);
	//int getIndex{return m_pSurface.}
};

