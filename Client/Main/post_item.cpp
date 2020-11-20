#include "stdafx.h"
#include "Defines.h"
#include "Import.h"
#include "Object.h"
#include "post_item.h"
#include "Interface.h"
#include "Protocol.h"
#include "Util.h"
#include "InfoLog.h"
#include <string>
// -----------------------------------------------------------------------------

PostItem gPostItem;
// -----------------------------------------------------------------------------

PostItem::PostItem () {
    list_counter_ = 0;
    last_tickcount_post_ = 0;
    current_item_post_ = &gInterface.item_post_;
    last_tickcount_view_ = &gInterface.last_tickcount_view_;
    draw_character_head_chat_text_ = false;
    PostItemColor = GetPrivateProfileInt ( "Game", "PostColor", 7, ".\\Settings.ini" );
    if ( PostItemColor < 1 || PostItemColor > 9 ){PostItemColor = 9;}


    Hook();
}
// -----------------------------------------------------------------------------

PostItem::~PostItem() {
}
// -----------------------------------------------------------------------------

void PostItem::Hook() {
	SetCompleteHook(0xE9,0x007DCFD0,&PostItemToWorldChatChannel);//1.04D-> 0x007DCE80
	SetCompleteHook(0xE9,0x007897C7,&BuildChatDataLong);//1.04D-> 0x00789677
	SetCompleteHook(0xE9,0x0078AAA6,&ViewPostItem);//1.04D->0x0078A956
	SetJmp(0x00599183,6,ProcessCharacterHeadChatText);
}
#include "Font.h"
void __declspec ( naked ) PostItem::PostItemToWorldChatChannel() {
    static DWORD register_ecx = 0;
    static DWORD register_edx = 0;
    static DWORD mem = 0;
    _asm {
        MOV register_ecx, ECX;
        MOV register_edx, EDX;
        MOV ECX, DWORD PTR SS : [EBP - 0x10];
        MOV EDX, DWORD PTR DS : [ECX + 0x54];
        MOV mem, EDX;
    }
    PostItemToWorldChatChannelImp ( ( void * ) mem );
    _asm {
        MOV ECX, register_ecx;
        MOV EDX, register_edx;
		MOV mem, 0x007DD09D; //1.04D-> 0x007DCF4D;
        JMP mem;
    }
}

// -----------------------------------------------------------------------------
void PostItem::PostItemToWorldChatChannelImp ( void * item_data ) {

    // check window, not allow for shop, inventory, warehouse, etc
    if ( gInterface.CheckWindow ( Trade ) ||
            gInterface.CheckWindow ( Warehouse ) ||
            gInterface.CheckWindow ( Shop ) ||
            gInterface.CheckWindow ( Store ) ||
            gInterface.CheckWindow ( OtherStore ) ||
            gInterface.CheckWindow ( CashShop ) ||
            gInterface.CheckWindow ( ExpandWarehouse ) ) {
        return;
    }

    if ( GetTickCount() <= gPostItem.last_tickcount_post_ + 3000 ) { return; }

    if ( GetKeyState ( VK_RBUTTON ) & 0x8000 && GetKeyState ( VK_CONTROL ) & 0x8000 ) {
        PMSG_POSTITEM iMsg = { '\0' };
		iMsg.h.set (0x78, sizeof ( iMsg ) );
        strcpy_s ( iMsg.chatmsg, ( char* ) pCurrentViewingItemName );
        memcpy_s ( &iMsg.chatid[0], 10, ( char* ) oUserObjectStruct_, 10 );
        memcpy_s ( &iMsg.item_data[0], 107, item_data, 107 );
        DataSend ( ( BYTE* ) &iMsg, iMsg.h.size );
        gPostItem.last_tickcount_post_ = GetTickCount();
    }
	/*
    // check window, not allow for shop, inventory, warehouse, etc
    if ( gInterface.CheckWindow ( Trade ) ||
            gInterface.CheckWindow ( Warehouse ) ||
            gInterface.CheckWindow ( Shop ) ||
            gInterface.CheckWindow ( Store ) ||
            gInterface.CheckWindow ( OtherStore ) ||
            gInterface.CheckWindow ( CashShop ) ||
            gInterface.CheckWindow ( ExpandWarehouse ) ) {
        return;
    }

    if ( GetKeyState ( VK_RBUTTON ) & 0x8000 ) {
        PMSG_POSTITEM iMsg = { '\0' };

        strcpy_s ( iMsg.chatmsg, ( char* ) pCurrentViewingItemName );
        memcpy_s ( &iMsg.chatid[0], 10, ( char* ) oUserObjectStruct_, 10 );
        memcpy_s ( &iMsg.item_data[0], 107, item_data, 107 );

		if (gInterface.CheckWindow(ChaosBox))
		{
				PMSG_INVENTORYITEMMOVE pSend;// = { '\0' };

				pSend.target_item_num = 0;

				if (pCursorX < 435)
				{
		
				} else {
					pSend.source_item_num = iMsg.item_data[68] * 8 + 12 + iMsg.item_data[67];
					pSend.sFlag = 0;
					pSend.tFlag = 3;
				}
			
				int itemType = iMsg.item_data[0] + ((iMsg.item_data[23]&0x80)*2); //+((buf[5]&0xF0)<<5);
				int buf5 = ((iMsg.item_data[1] / 2) * 512) >> 5;

				pSend.sItemInfo[0] = iMsg.item_data[0];
				pSend.sItemInfo[1] = iMsg.item_data[2];
				pSend.sItemInfo[2] = iMsg.item_data[22];
				pSend.sItemInfo[3] = iMsg.item_data[23]; // 3
				pSend.sItemInfo[4] = iMsg.item_data[24]; // SET
				pSend.sItemInfo[5] = buf5; // 5
				pSend.sItemInfo[6] = (BYTE)(iMsg.item_data[69] << 4) + iMsg.item_data[71];
				pSend.sItemInfo[7] = iMsg.item_data[74];
				pSend.sItemInfo[8] = iMsg.item_data[75];
				pSend.sItemInfo[9] = iMsg.item_data[76];
				pSend.sItemInfo[10] = iMsg.item_data[77];
				pSend.sItemInfo[11] = iMsg.item_data[78];

				pSend.h.set(0xF9,sizeof(pSend));
				DataSend((BYTE*)&pSend,pSend.h.size);
		}

		if ( GetTickCount() <= gPostItem.last_tickcount_post_ + 3000 ) { return; }

		if(GetKeyState ( VK_CONTROL ) & 0x8000)
		{
			iMsg.h.set (0x78, sizeof ( iMsg ) );
			DataSend ( ( BYTE* ) &iMsg, iMsg.h.size );
			gPostItem.last_tickcount_post_ = GetTickCount();
		}
    }
	*/
}
// -----------------------------------------------------------------------------

void * PostItem::AddItem ( void * item_data ) {
    LinkNode<ItemPost> * item = new ItemPost ( item_data );
    gPostItem.list_.Append ( item );

    if ( gPostItem.list_counter_ >= MAX_CHAT_MESSAGE ) {
        LinkNode<ItemPost> * node = gPostItem.list_.head();
        node->Free();
    }
    else {
        gPostItem.list_counter_++;
    }

    return item;
}
// -----------------------------------------------------------------------------

void __declspec ( naked ) PostItem::BuildChatDataLong() {
    static void * chat_data_pointer = nullptr;
    static DWORD mem = 0;
    _asm {
        MOV chat_data_pointer, ECX;
		MOV mem, 0x0078BFE0; //1.04D-> 0x0078BE90;
        CALL mem;
    }
    BuildChatData ( chat_data_pointer );
    _asm {
		MOV mem, 0x007897CC; //1.04D-> 0x0078967C;
        JMP mem;
    }
}
// -----------------------------------------------------------------------------

void __declspec ( naked ) PostItem::BuildChatDataShort() {
    static void * chat_data_pointer = nullptr;
    static DWORD mem = 0;
    _asm {
        MOV chat_data_pointer, ECX;
		MOV mem, 0x0078BFE0; //1.04D-> 0x0078BE90;
        CALL mem;
    }
    BuildChatData ( chat_data_pointer );
    _asm {
		MOV mem, 0x00789E17; //1.04D-> 0x00789CC7;
        JMP mem;
    }
}
// -----------------------------------------------------------------------------

void PostItem::BuildChatData ( void * chat_data_pointer ) {
    MuObjectChatData * chat = ( MuObjectChatData * ) chat_data_pointer;

    if ( !chat->is_external_message() || !gPostItem.list_counter_ ) {
        return;
    }

    char * message = chat->message();
    unsigned long message_len = chat->message_len();

    // _APIxxXXXXxxAPI
    if ( message[message_len - 1 - 8 - 2] != '_' ||
            message[message_len - 1 - 8 - 1] != '[' ||
            message[message_len - 1] != ']' ) {
        return;
    }

    LinkNode<ItemPost> * item_node = nullptr;
    sscanf_s ( &message[message_len - 1 - 8], "%08X", ( DWORD * ) &item_node );
    ItemPost * item_post = item_node->value();
    item_post->chat_ = chat;
    message[message_len - 1 - 8 - 2] = '\0';
    message[message_len - 1 - 8 + 0] = '_';
    message[message_len - 1 - 8 + 1] = '_';
    message[message_len - 1 - 8 + 6] = '_';
    message[message_len - 1 - 8 + 7] = '_';
    * ( unsigned long * ) &message[message_len - 1 - 8 + 2] = ( unsigned long ) item_node;
}
// -----------------------------------------------------------------------------

void __declspec ( naked ) PostItem::ProcessCharacterHeadChatText() {
    static DWORD mem = 0;
    static DWORD base_address;
    static DWORD chat_text;
    _asm {
        MOV mem, EAX;
        MOV EAX, DWORD PTR SS : [EBP + 0x08];
        MOV base_address, EAX;
        MOV EAX, DWORD PTR SS : [EBP + 0x0C];
        MOV chat_text, EAX;
        MOV EAX, mem;
    }
    PostItem::ProcessCharacterHeadChatTextImp ( ( char * ) base_address, ( char * ) chat_text );
    _asm {
        PUSH -1;
		PUSH 0x00CD3143; //1.04D-> 0x00CD2FC3;
        MOV mem, 0x0059918A;
        JMP mem;
    }
}
// -----------------------------------------------------------------------------

void PostItem::ProcessCharacterHeadChatTextImp ( char * base_address, char * chat_text ) {
    if ( gPostItem.draw_character_head_chat_text_ ) {
        // xử lý đoạn chat trên đầu nhân vật
        unsigned long len = strlen ( chat_text );

        if ( chat_text[len - 1 - 8 - 2] != '_' ||
                chat_text[len - 1 - 8 - 1] != '[' ||
                chat_text[len - 1] != ']' ) {
            // do nothing
        }
        else {
            gPostItem.draw_character_head_chat_text_base_address_ = base_address;
        }

        gPostItem.draw_character_head_chat_text_ = false;
    }
}
// -----------------------------------------------------------------------------

void __declspec ( naked ) PostItem::ViewPostItem() {
    static void * chat_data_pointer = nullptr;
    static DWORD mem = 0;
    _asm {
		MOV mem, 0x0078C020; //1.04D-> 0x0078BED0;
        CALL mem;
        MOV chat_data_pointer, EAX;
    }
    ViewPostItemImp ( chat_data_pointer );
    _asm {
        MOV EAX, chat_data_pointer;
		MOV mem, 0x0078AAAB; //1.04D-> 0x0078A95B;
        JMP mem;
    }
}
// -----------------------------------------------------------------------------
#include "User.h"
void PostItem::ViewPostItemImp ( void * chat_data_pointer ) {
    MuObjectChatData * chat = ( MuObjectChatData * ) chat_data_pointer;

    if ( !chat->is_external_message() || !gPostItem.list_counter_ ) {
        *gPostItem.current_item_post_ = nullptr;
        return;
    }

    char * message = chat->message();
    unsigned long message_len = chat->message_len();
    unsigned long real_len = strlen ( message );

    if ( message_len == real_len ) {
        *gPostItem.current_item_post_ = nullptr;
        return;
    }

    // _API__XXXX__API
    if ( message[message_len - 1 - 8 - 2] != '\0' ||
            message[message_len - 1 - 8 - 1] != '[' ||
            message[message_len - 1] != ']' ) {
        *gPostItem.current_item_post_ = nullptr;
        return;
    }

    LinkNode<ItemPost> * item_node = ( LinkNode<ItemPost> * ) * ( unsigned long * ) &message[message_len - 1 - 8 + 2];
    ItemPost * item_post = item_node->value();
    ObjectItem * item_data = ( ObjectItem * ) &item_post->item_;
    // set show item tool tip
    *gPostItem.last_tickcount_view_ = GetTickCount();
    *gPostItem.current_item_post_ = item_data;
	gObjUser.PostItemID = item_data->ItemID;
	gObjUser.PostItemLV = item_data->Level;
	gObjUser.PostItemExc = item_data->ExcellentOption;
	gObjUser.PostItemX = item_data->PosX;
	gObjUser.PostItemY = item_data->PosY;
}
// -----------------------------------------------------------------------------