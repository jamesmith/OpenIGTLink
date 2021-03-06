/*=========================================================================

  Program:   Open IGT Link Library
  Module:    $HeadURL: http://svn.na-mic.org/NAMICSandBox/trunk/OpenIGTLink2_beta/Source/igtlStatusMessage.cxx $
  Language:  C++
  Date:      $Date: 2010-01-17 13:04:20 -0500 (Sun, 17 Jan 2010) $
  Version:   $Revision: 5575 $

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "igtlPointMessage.h"

#include "igtl_header.h"
#include "igtl_point.h"

// Disable warning C4996 (strncpy() may be unsafe) in Windows. 
#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <vector>

namespace igtl {


//----------------------------------------------------------------------
// igtl::PointElement class

PointElement::PointElement() : Object()
{
  this->m_Name        = "";
  this->m_GroupName   = "";
  this->m_RGBA[0]     = 0;
  this->m_RGBA[1]     = 0;
  this->m_RGBA[2]     = 0;
  this->m_RGBA[3]     = 0;
  this->m_Position[0] = 0.0;
  this->m_Position[1] = 0.0;
  this->m_Position[2] = 0.0;
  this->m_Radius      = 0.0;
  this->m_Owner       = "";
}


PointElement::~PointElement()
{
}


int PointElement::SetName(const char* name)
{
  if (strlen(name) <= IGTL_POINT_LEN_NAME)
    {
    this->m_Name = name;
    return 1;
    }
  else
    {
    return 0;
    }
}


int PointElement::SetGroupName(const char* grpname)
{
  if (strlen(grpname) <= IGTL_POINT_LEN_GROUP_NAME)
    {
    this->m_GroupName = grpname;
    return 1;
    }
  else
    {
    return 0;
    }
}


void PointElement::SetRGBA(igtlUint8 rgba[4])
{
  this->m_RGBA[0] = rgba[0];
  this->m_RGBA[1] = rgba[1];
  this->m_RGBA[2] = rgba[2];
  this->m_RGBA[3] = rgba[3];
}


void PointElement::SetRGBA(igtlUint8 r, igtlUint8 g, igtlUint8 b, igtlUint8 a)
{
  this->m_RGBA[0] = r;
  this->m_RGBA[1] = g;
  this->m_RGBA[2] = b;
  this->m_RGBA[3] = a;
}


void PointElement::GetRGBA(igtlUint8* rgba)
{
  rgba[0] = this->m_RGBA[0];
  rgba[1] = this->m_RGBA[1];
  rgba[2] = this->m_RGBA[2];
  rgba[3] = this->m_RGBA[3];
}  



void PointElement::GetRGBA(igtlUint8& r, igtlUint8& g, igtlUint8& b, igtlUint8& a)
{
  r = this->m_RGBA[0];
  g = this->m_RGBA[1];
  b = this->m_RGBA[2];
  a = this->m_RGBA[3];
}

void PointElement::SetPosition(igtlFloat32 position[3])
{
  this->m_Position[0] = position[0];
  this->m_Position[1] = position[1];
  this->m_Position[2] = position[2];
}


void PointElement::SetPosition(igtlFloat32 x, igtlFloat32 y, igtlFloat32 z)
{
  this->m_Position[0] = x;
  this->m_Position[1] = y;
  this->m_Position[2] = z;
}


void PointElement::GetPosition(igtlFloat32* position)
{
  position[0] = this->m_Position[0];
  position[1] = this->m_Position[1];
  position[2] = this->m_Position[2];
}


void PointElement::GetPosition(igtlFloat32& x, igtlFloat32& y, igtlFloat32& z)
{
  x = this->m_Position[0];
  y = this->m_Position[1];
  z = this->m_Position[2];
}

int PointElement::SetOwner(const char* owner)
{
  if (strlen(owner) <= IGTL_POINT_LEN_OWNER)
    {
    this->m_Owner = owner;
    return 1;
    }
  else
    {
    return 0;
    }
}


//----------------------------------------------------------------------
// igtl::PointMessage class

PointMessage::PointMessage():
  MessageBase()
{
  this->m_DefaultBodyType = "POINT";
  this->m_PointList.clear();
}


PointMessage::~PointMessage()
{
}


int PointMessage::AddPointElement(PointElement::Pointer& elem)
{
  this->m_PointList.push_back(elem);
  return this->m_PointList.size();
}


void PointMessage::ClearPointElement()
{
  this->m_PointList.clear();
}


int PointMessage::GetNumberOfPointElement()
{
  return this->m_PointList.size();
}


void PointMessage::GetPointElement(int index, PointElement::Pointer& elem)
{
  if (index >= 0 && index < (int)this->m_PointList.size())
    {
    elem = this->m_PointList[index];
    }
}


int PointMessage::GetBodyPackSize()
{
  // The body size sum of the header size and status message size.
  return IGTL_POINT_ELEMENT_SIZE * this->m_PointList.size();
}


int PointMessage::PackBody()
{
  // allocate pack
  AllocatePack();
  
  igtl_point_element* element;

  element = (igtl_point_element*)this->m_Body;

  std::vector<PointElement::Pointer>::iterator iter;
  for (iter = this->m_PointList.begin(); iter != this->m_PointList.end(); iter ++)
    {
    strncpy((char*)element->name,       (*iter)->GetName(),      IGTL_POINT_LEN_NAME);
    strncpy((char*)element->group_name, (*iter)->GetGroupName(), IGTL_POINT_LEN_GROUP_NAME);

    igtlUint8 rgba[4];
    (*iter)->GetRGBA(rgba);
    element->rgba[0] = rgba[0];
    element->rgba[1] = rgba[1];
    element->rgba[2] = rgba[2];
    element->rgba[3] = rgba[3];

    igtlFloat32 position[3];
    (*iter)->GetPosition(position);
    element->position[0] = position[0];
    element->position[1] = position[1];
    element->position[2] = position[2];

    element->radius = (*iter)->GetRadius();

    strncpy((char*)element->owner,  (*iter)->GetOwner(), IGTL_POINT_LEN_OWNER);
    
    element ++;
    }

  igtl_point_convert_byte_order((igtl_point_element*)this->m_Body, this->m_PointList.size());

  return 1;
}


int PointMessage::UnpackBody()
{

  this->m_PointList.clear();

  igtl_point_element* element = (igtl_point_element*) this->m_Body;
  int nElement = igtl_point_get_data_n(this->m_BodySizeToRead);

  igtl_point_convert_byte_order(element, nElement);
  
  char strbuf[128];
  for (int i = 0; i < nElement; i ++)
    {
    PointElement::Pointer elemClass = PointElement::New();

    // Add '\n' at the end of each string
    // (neccesary for a case, where a string reaches the maximum length.)
    strbuf[IGTL_POINT_LEN_NAME] = '\n';
    strncpy(strbuf, (char*)element->name, IGTL_POINT_LEN_NAME);
    elemClass->SetName((const char*)strbuf);
    
    strbuf[IGTL_POINT_LEN_GROUP_NAME] = '\n';
    strncpy(strbuf, (char*)element->group_name, IGTL_POINT_LEN_GROUP_NAME);
    elemClass->SetGroupName(strbuf);

    elemClass->SetRGBA(element->rgba);
    elemClass->SetPosition(element->position);
    elemClass->SetRadius(element->radius);

    strbuf[IGTL_POINT_LEN_OWNER] = '\n';
    strncpy(strbuf, (char*)element->owner, IGTL_POINT_LEN_OWNER);
    elemClass->SetOwner(strbuf);

    this->m_PointList.push_back(elemClass);

    element ++;
    }

  return 1;
}

} // namespace igtl





