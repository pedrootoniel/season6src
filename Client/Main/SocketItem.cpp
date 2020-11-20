#include "stdafx.h"
#include "SocketItem.h"
#include "Import.h"
#include "Util.h"
#include "Item.h"
#include "Defines.h"
#include "CustomSocket.h"

cSocketItem gSocketItem;

void cSocketItem::Load()
{

	SetCompleteHook(0xE8,0x00968141,&this->CheckItem);
	SetCompleteHook(0xE8,0x00968167,&this->CheckItem);

	// Fix Socket + joh
	//SetByte(0x008385E4, 0xEB);	//-> 1.04E
	//SetByte(0x00838647, 0xEB);	//-> 1.04E
	//SetByte(0x00838658, 0xEB);	//-> 1.04E
	//		//SetByte(0x008385F5, 0xEB);	//-> 1.04E
	//SetByte(0x005BD939, 0xEB);	//-> 1.04E
	//SetByte(0x007E1DE1, 0xEB);	//-> 1.04E
	//SetNop(0x007E5429,6); // fix show Option JOH		 1.04E
}

int cSocketItem::CheckItem(signed int ItemCode)
{
	for(int n = 0; n < MAX_CUSTOM_SOCKET; n++ )
	{
		if( ItemCode == GET_ITEM(0,0))
		{
			return 0;
		}
		else if( ItemCode == GET_ITEM(gCustomSocket.m_CustomSocketInfo[n].SocketType, gCustomSocket.m_CustomSocketInfo[n].SocketIndex) )
		{
			return 1;
		}
		else if( gCustomSocket.m_CustomSocketInfo[n].SocketType == -1 )
		{
			for( int Category = 7; Category < 12; Category++ )
			{
				if( ItemCode == GET_ITEM(Category, gCustomSocket.m_CustomSocketInfo[n].SocketIndex) )
				{
					return 1;
				}
			}
		}
	}
	return 0;
}
