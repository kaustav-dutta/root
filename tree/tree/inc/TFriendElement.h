// @(#)root/tree:$Id$
// Author: Rene Brun   07/04/2001

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/
#ifndef ROOT_TFriendElement
#define ROOT_TFriendElement


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TFriendElement                                                       //
//                                                                      //
// A TFriendElement TF describes a TTree object TF in a file.           //
// When a TFriendElement TF is added to the the list of friends of an   //
// existing TTree T, any variable from TF can be referenced in a query  //
// to T.                                                                //
//                                                                      //
//////////////////////////////////////////////////////////////////////////


#include "TNamed.h"

class TFile;
class TTree;
class TChain;
class TClass;

class TFriendElement : public TNamed {

protected:
   TTree        *fParentTree;  ///<! pointer to the parent TTree
   TTree        *fTree;        ///<! pointer to the TTree described by this element
   TFile        *fFile;        ///<! pointer to the file containing the friend TTree
   TString       fTreeName;    ///<  name of the friend TTree
   Bool_t        fOwnFile;     ///<  true if file is managed by this class

   TFriendElement(const TFriendElement&) = delete;
   TFriendElement& operator=(const TFriendElement&) = delete;

   friend void TFriendElement__SetTree(TTree *tree, TList *frlist);
   friend class TChain;

public:
   enum EStatusBits { kFromChain = BIT(11) };
   TFriendElement();
   TFriendElement(TTree *tree, const char *treename, const char *filename);
   TFriendElement(TTree *tree, const char *treename, TFile *file);
   TFriendElement(TTree *tree, TTree* friendtree, const char *alias);
   virtual ~TFriendElement();
   virtual TTree      *Connect();
   virtual TTree      *DisConnect();
   virtual TFile      *GetFile(Bool_t load = kTRUE);
   virtual TTree      *GetParentTree() const {return fParentTree;}
   virtual TTree      *GetTree(Bool_t load = kTRUE);
   virtual const char *GetTreeName() const {return fTreeName.Data();}
   virtual void        ls(Option_t *option="") const;
   virtual void        RecursiveRemove(TObject *obj);

   ClassDef(TFriendElement,2)  //A friend element of another TTree
};

#endif

