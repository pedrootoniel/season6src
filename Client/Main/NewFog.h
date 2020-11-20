#ifndef __NEWFOG_H__
#define __NEWFOG_H__


class cNewFog
{
public:    void Init();
    void Load();
        void MainFogAllowed();
        // ----
        static void glMainDisable();

    static bool CheckBlackMaps();
    static bool CheckEventMaps();
    static void glMainEnable(GLenum cap);
    static bool glAllowedFog(GLenum cap);
};


extern cNewFog gNewFog;


#endif