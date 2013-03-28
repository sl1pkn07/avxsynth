// Avisynth v4.0  Copyright 2002 Ben Rudiak-Gould et al.
// http://www.avisynth.org
// http://www.avxsynth.org


// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA, or visit
// http://www.gnu.org/copyleft/gpl.html .
//
// Linking Avisynth statically or dynamically with other modules is making a
// combined work based on Avisynth.  Thus, the terms and conditions of the GNU
// General Public License cover the whole combination.
//
// As a special exception, the copyright holders of Avisynth give you
// permission to link Avisynth with independent modules that communicate with
// Avisynth solely through the interfaces defined in avisynth.h, regardless of the license
// terms of these independent modules, and to copy and distribute the
// resulting combined work under terms of your choice, provided that
// every copy of the combined work is accompanied by a complete copy of
// the source code of Avisynth (the version of Avisynth used to produce the
// combined work), being distributed under the terms of the GNU General
// Public License plus this exception.  An independent module is a module
// which is not derived from or based on Avisynth, such as 3rd-party filters,
// import and export plugins, or graphical user interfaces.


// Avisynth filter: YUV merge
// by Klaus Post
// adapted by Richard Berg (avisynth-dev@richardberg.net)


#ifndef __Merge_H__
#define __Merge_H__

#include "internal.h"

namespace avxsynth {
	
/****************************************************
****************************************************/

class MergeChroma : public GenericVideoFilter
/**
  * Merge the chroma planes of one clip into another, preserving luma
 **/
{
public:
  MergeChroma(PClip _child, PClip _clip, float _weight, int _test, IScriptEnvironment* env);  
  PVideoFrame __stdcall GetFrame(int n, IScriptEnvironment* env);

  static AVSValue __cdecl Create(AVSValue args, void* user_data, IScriptEnvironment* env);

private:
  PClip clip;
  float weight;
  int test;
};


class MergeLuma : public GenericVideoFilter
/**
  * Merge the luma plane of one clip into another, preserving chroma
 **/
{
public:
  MergeLuma(PClip _child, PClip _clip, float _weight, int _test, IScriptEnvironment* env);  
  PVideoFrame __stdcall GetFrame(int n, IScriptEnvironment* env);

  static AVSValue __cdecl Create(AVSValue args, void* user_data, IScriptEnvironment* env);

private:
  PClip clip;
  float weight;
  int test;
};


class MergeAll : public GenericVideoFilter
/**
  * Merge the planes of one clip into another
 **/
{
public:
  MergeAll(PClip _child, PClip _clip, float _weight, int _test, IScriptEnvironment* env);  
  PVideoFrame __stdcall GetFrame(int n, IScriptEnvironment* env);

  static AVSValue __cdecl Create(AVSValue args, void* user_data, IScriptEnvironment* env);

private:
  PClip clip;
  float weight;
  int test;
};



#ifdef ENABLE_INLINE_ASSEMBLY_MMX_SSE
/**** MMX Routines ****/

void mmx_merge_luma( unsigned int *src, unsigned int *luma, int pitch, 
                     int luma_pitch, int width, int height );
                    
void mmx_weigh_luma( unsigned int *src, unsigned int *luma, int pitch, 
                     int luma_pitch, int width, int height, int weight, int invweight );

void mmx_weigh_chroma( unsigned int *src,unsigned int *chroma, int pitch, 
                       int chroma_pitch, int width, int height, int weight, int invweight );
#endif // ENABLE_INLINE_ASSEMBLY_MMX_SSE

void merge_luma( unsigned int *src, unsigned int *luma, int pitch, 
                     int luma_pitch, int width, int height );
                    
void weigh_luma( unsigned int *src, unsigned int *luma, int pitch,
                 int luma_pitch, int width, int height, int weight, int invweight);

void weigh_chroma( unsigned int *src, unsigned int *chroma, int pitch,
                   int chroma_pitch, int width, int height, int weight, int invweight);

#ifdef ENABLE_INLINE_ASSEMBLY_MMX_SSE
void mmx_weigh_plane(BYTE *p1,const BYTE *p2, int p1_pitch, int p2_pitch,int rowsize, int height, int weight, int invweight);
#endif // ENABLE_INLINE_ASSEMBLY_MMX_SSE

void weigh_plane(BYTE *p1,const BYTE *p2, int p1_pitch, int p2_pitch,int rowsize, int height, int weight, int invweight);

#ifdef ENABLE_INLINE_ASSEMBLY_MMX_SSE
void isse_avg_plane(BYTE *p1,const BYTE *p2, int p1_pitch, int p2_pitch,int rowsize, int height);
#endif // ENABLE_INLINE_ASSEMBLY_MMX_SSE

}; // namespace avxsynth
#endif  // __Merge_H__
