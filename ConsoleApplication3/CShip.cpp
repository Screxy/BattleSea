#include "CShip.h"
#include "CCell.h"

CShip::CShip()
{
	m_Deck = 0;
}
CShip::CShip(int deck)
{
	m_Deck = deck;
	m_pCells.clear();
}
CShip::~CShip()
{

}
bool CShip::IsPlaced()
{
	for (int i = 0; i < m_Deck; i++)
		if (!m_pCells[i])
			return false;

	return true;
}
void CShip::ClearCells()
{
	for (int i = 0; i < m_pCells.size(); i++)
		m_pCells[i]->m_pShip = NULL;

}
bool CShip::Alive()
{
	for (int i = 0; i < m_Deck; i++)
		if (!m_pCells[i]->m_bBeated)
			return true;


	return false;
}