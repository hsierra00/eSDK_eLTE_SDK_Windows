/*
mediastreamer2 library - modular sound and video processing and streaming
Copyright (C) 2006  Simon MORLAT (simon.morlat@linphone.org)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef ice_hh
#define ice_hh

#include "msfilter.h"
#include "ortp/stun_udp.h"
#include "ortp/stun.h"
#include "ortp/turn.h"
#include "ortp/ortp.h"


#define MS_ICE_SET_SESSION			MS_FILTER_METHOD(MS_ICE_ID,0,RtpSession*)
#define MS_ICE_SET_CANDIDATEPAIRS	MS_FILTER_METHOD(MS_ICE_ID,1,struct CandidatePair*)

extern MSFilterDesc ms_ice_desc;

#endif
