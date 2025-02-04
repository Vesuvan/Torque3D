//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#ifndef SHAPE_ANIMATION_ASSET_H
#define SHAPE_ANIMATION_ASSET_H

#ifndef _ASSET_BASE_H_
#include "assets/assetBase.h"
#endif

#ifndef _ASSET_DEFINITION_H_
#include "assets/assetDefinition.h"
#endif

#ifndef _STRINGUNIT_H_
#include "string/stringUnit.h"
#endif

#ifndef _ASSET_FIELD_TYPES_H_
#include "assets/assetFieldTypes.h"
#endif
#ifndef _TSSHAPE_H_
#include "ts/tsShape.h"
#endif
#ifndef __RESOURCE_H__
#include "core/resource.h"
#endif

#ifndef _ASSET_PTR_H_
#include "assets/assetPtr.h"
#endif

#include "assetMacroHelpers.h"

//-----------------------------------------------------------------------------
class ShapeAnimationAsset : public AssetBase
{
   typedef AssetBase Parent;
   typedef AssetPtr<ShapeAnimationAsset> ConcreteAssetPtr;
protected:
   StringTableEntry   mFileName;
   StringTableEntry   mFilePath;

   bool            mIsEmbedded;
   bool            mIsCyclical;

   bool            mIsBlend;

   StringTableEntry mBlendAnimAssetName;

   S32 mBlendFrame;

   //
   StringTableEntry mAnimationName;
   S32 mStartFrame;
   S32 mEndFrame;
   bool mPadRotation;
   bool mPadTransforms;

   Resource<TSShape> mSourceShape;

public:
   enum ShapeAnimationAssetErrCode
   {
      TooManyBones = AssetErrCode::Extended,
      Extended
   };

   static const String mErrCodeStrings[U32(ShapeAnimationAssetErrCode::Extended) - U32(Parent::Extended) + 1];
   static U32 getAssetErrCode(ConcreteAssetPtr checkAsset) { if (checkAsset) return checkAsset->mLoadedState; else return 0; }

   static String getAssetErrstrn(U32 errCode)
   {
      if (errCode < Parent::Extended) return Parent::getAssetErrstrn(errCode);
      if (errCode > ShapeAnimationAssetErrCode::Extended) return "undefined error";
      return mErrCodeStrings[errCode - Parent::Extended];
   };
   ShapeAnimationAsset();
   virtual ~ShapeAnimationAsset();

   /// Engine.
   static void initPersistFields();
   virtual void copyTo(SimObject* object);

   void                    setAnimationFile(const char* pAnimationFile);
   inline StringTableEntry getAnimationFile(void) const { return mFileName; };

   inline StringTableEntry getAnimationPath(void) const { return mFilePath; };

   /// Declare Console Object.
   DECLARE_CONOBJECT(ShapeAnimationAsset);

protected:
   virtual void            initializeAsset(void);
   virtual void            onAssetRefresh(void);

   static bool setAnimationFile(void *obj, const char *index, const char *data) { static_cast<ShapeAnimationAsset*>(obj)->setAnimationFile(data); return false; }
   static const char* getAnimationFile(void* obj, const char* data) { return static_cast<ShapeAnimationAsset*>(obj)->getAnimationFile(); }

public:
   StringTableEntry getAnimationFilename() { return mFileName; }
   StringTableEntry getAnimationName() { return mAnimationName; }
   StringTableEntry getBlendAnimationName() { return mBlendAnimAssetName; }

   S32 getStartFrame() { return mStartFrame; }
   S32 getEndFrame() { return mEndFrame; }

   bool getPadRotation() { return mPadRotation; }
   bool getPadTransforms() { return mPadTransforms; }

   bool isEmbedded() { return mIsEmbedded; }
   bool isCyclic() { return mIsCyclical; }
   bool isBlend() { return mIsBlend; }

   S32 getBlendFrame() { return mBlendFrame; }

   S32 getAnimationCount();
};

DefineConsoleType(TypeShapeAnimationAssetPtr, ShapeAnimationAsset)
#ifdef TORQUE_TOOLS
//-----------------------------------------------------------------------------
// TypeAssetId GuiInspectorField Class
//-----------------------------------------------------------------------------
/*class GuiInspectorTypeShapeAnimationAssetPtr : public GuiInspectorTypeFileName
{
   typedef GuiInspectorTypeFileName Parent;
public:

   GuiBitmapButtonCtrl  *mShapeEdButton;

   DECLARE_CONOBJECT(GuiInspectorTypeShapeAnimationAssetPtr);
   static void consoleInit();

   virtual GuiControl* constructEditControl();
   virtual bool updateRects();
};*/
#endif
#endif // _ASSET_BASE_H_

