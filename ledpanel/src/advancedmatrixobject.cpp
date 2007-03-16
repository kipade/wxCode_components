/***************************************************************
 * Name:      advancedmatrixobejct.cpp
 * Purpose:   Code for Class AdvancedMatrixObject
 * Author:    Christian Gr�fe (info@mcs-soft.de)
 * Created:   2007-03-02
 * Copyright: Christian Gr�fe (www.mcs-soft.de)
 * License:	  wxWindows licence
 **************************************************************/

#include "wx/advancedmatrixobject.h"

AdvancedMatrixObject::AdvancedMatrixObject() :
	MatrixObject()
{
}

AdvancedMatrixObject::AdvancedMatrixObject(const MatrixObject& mo) :
	MatrixObject(mo)
{
}

AdvancedMatrixObject::AdvancedMatrixObject(const char* data, int width, int height) :
	MatrixObject(data,width,height)
{
}

AdvancedMatrixObject::~AdvancedMatrixObject()
{
}

////////////////////////////////////////////////////////////////
// Rotierfunktionen
////////////////////////////////////////////////////////////////
void AdvancedMatrixObject::RotateLeft()
{
	// is init?
	if(!m_data)
	{
		wxFAIL_MSG(wxT("AdvancedMatrixObject has no data to rotate!"));
		return;
	}

	// create tmp-object
	MatrixObject tmp=MatrixObject(0,m_height,m_width);

	int x, y;
	for(x=0;x<m_width;++x)
		for(y=0;y<m_height;++y)
			tmp.SetDataAt(y,m_width-x-1,this->GetDataFrom(x,y));

	// Daten �bernehmen
	for(int i=0;i<m_length;++i)
		m_data[i]=tmp.GetDataFrom(i);
	m_width=tmp.GetWidth();
	m_height=tmp.GetHeight();
}

void AdvancedMatrixObject::RotateRight()
{
	// is init?
	if(!m_data)
	{
		wxFAIL_MSG(wxT("AdvancedMatrixObject has no data to rotate!"));
		return;
	}

	// create tmp-object
	MatrixObject tmp=MatrixObject(0,m_height,m_width);

	int x, y;
	for(x=0;x<m_width;++x)
		for(y=0;y<m_height;++y)
			tmp.SetDataAt(m_height-y-1,x,this->GetDataFrom(x,y));

	// Daten �bernehmen
	for(int i=0;i<m_length;++i)
		m_data[i]=tmp.GetDataFrom(i);
	m_width=tmp.GetWidth();
	m_height=tmp.GetHeight();
}

////////////////////////////////////////////////////////////////
// Shiftfunktionen
////////////////////////////////////////////////////////////////
void AdvancedMatrixObject::ShiftLeft()
{
	// is init?
	if(!m_data)
	{
		wxFAIL_MSG(wxT("AdvancedMatrixObject has no data to shift!"));
		return;
	}

	// alles nach links verschieben
	char* tmp=m_data;
	tmp++;
	memmove(m_data,tmp,(m_length-1)*sizeof(char));

	// rechter rand muss jetzt leer sein
	for(int i=0;i<m_height;++i)
		SetDataAt(m_width-1,i,0);
}

void AdvancedMatrixObject::ShiftRight()
{
	// is init?
	if(!m_data)
	{
		wxFAIL_MSG(wxT("AdvancedMatrixObject has no data to shift!"));
		return;
	}

	// alles nach rechts verschieben
	char* tmp=m_data;
	tmp++;
	memmove(tmp,m_data,(m_length-1)*sizeof(char));

	// linker rand muss jetzt leer sein
	for(int i=0;i<m_height;++i)
		SetDataAt(0,i,0);
}

void AdvancedMatrixObject::ShiftUp()
{
	// is init?
	if(!m_data)
	{
		wxFAIL_MSG(wxT("AdvancedMatrixObject has no data to shift!"));
		return;
	}

	// alles nach oben verschieben
	char* tmp=m_data;
	tmp+=m_width*sizeof(char);
	memmove(m_data,tmp,(m_length-1-m_width)*sizeof(char));

	// unterer rand muss jetzt leer sein
	for(int i=0;i<m_width;++i)
		SetDataAt(i,m_height-1,0);
}

void AdvancedMatrixObject::ShiftDown()
{
	// is init?
	if(!m_data)
	{
		wxFAIL_MSG(wxT("AdvancedMatrixObject has no data to shift!"));
		return;
	}

	// alles nach rechts verschieben
	char* tmp=m_data;
	tmp+=m_width*sizeof(char);
	memmove(tmp,m_data,(m_length-1-m_width)*sizeof(char));

	// oberer rand muss jetzt leer sein
	for(int i=0;i<m_width;++i)
		SetDataAt(i,0,0);
}

////////////////////////////////////////////////////////////////
// Fitfunktionen
////////////////////////////////////////////////////////////////
void AdvancedMatrixObject::FitLeft()
{
	// is init?
	if(!m_data)
	{
		wxFAIL_MSG(wxT("AdvancedMatrixObject has no data to fit!"));
		return;
	}

	// Linken Rand Testen
	bool test=true;
	int i,emptyLines=-1;
	while(test)
	{
		++emptyLines;
		for(i=0; i<m_height; ++i)
		{
			if(m_data[emptyLines+i*m_width]!=0)	// GetDataFrom(emptyLines,i)
			{
				test=false;
				break;
			}
		}
	}

	// Daten neu speichern
	if(emptyLines>0)
	{
		int x=0,y=0,p=0;
		char* tmp=new char[(m_width-emptyLines)*m_height];
		for(y=0;y<m_height;++y)
			for(x=emptyLines;x<m_width;++x)
			{
				tmp[p]=GetDataFrom(x,y);
				++p;
			}
		delete [] m_data;
		m_data=tmp;
		m_width-=emptyLines;
		m_length=m_width*m_height;
	}
}

void AdvancedMatrixObject::FitRight()
{
	// is init?
	if(!m_data)
	{
		wxFAIL_MSG(wxT("AdvancedMatrixObject has no data to fit!"));
		return;
	}

	// Rechten Rand Testen
	bool test=true;
	int i,emptyLines=-1;
	while(test)
	{
		++emptyLines;
		for(i=0; i<m_height; ++i)
			if(m_data[(m_width-emptyLines-1)+i*m_width]!=0)	// GetDataFrom(m_width-emptyLines-1,i)
			{
				test=false;
				break;
			}
	}

	// Daten neu speichern
	if(emptyLines>0)
	{
		int new_width=m_width-emptyLines;
		int x=0,y=0,p=0;
		char* tmp=new char[new_width*m_height];
		for(y=0;y<m_height;++y)
			for(x=0;x<new_width;++x)
			{
				tmp[p]=GetDataFrom(x,y);
				++p;
			}
		delete [] m_data;
		m_data=tmp;
		m_width=new_width;
		m_length=m_width*m_height;
	}
}

void AdvancedMatrixObject::FitTop()
{
	// is init?
	if(!m_data)
	{
		wxFAIL_MSG(wxT("AdvancedMatrixObject has no data to fit!"));
		return;
	}

	// oberen Rand Testen
	bool test=true;
	int i,emptyLines=-1;
	while(test)
	{
		++emptyLines;
		for(i=0; i<m_width; ++i)
			if(m_data[i+emptyLines*m_width]!=0)	// GetDataFrom(i,emptyLines)
			{
				test=false;
				break;
			}
	}

	// Daten neu speichern
	if(emptyLines>0)
	{
		int new_height=m_height-emptyLines;
		int new_length=new_height*m_width;
		char* tmp=new char[new_length];

		memcpy(tmp,m_data+sizeof(char)*emptyLines*m_width,new_length*sizeof(char));

		delete [] m_data;
		m_data=tmp;
		m_height=new_height;
		m_length=new_length;
	}
}

void AdvancedMatrixObject::FitBottom()
{
	// is init?
	if(!m_data)
	{
		wxFAIL_MSG(wxT("AdvancedMatrixObject has no data to fit!"));
		return;
	}

	// unteren Rand Testen
	bool test=true;
	int i,emptyLines=-1;
	while(test)
	{
		++emptyLines;
		for(i=0; i<m_width; ++i)
			if(m_data[i+(m_height-emptyLines-1)*m_width]!=0)	// GetDataFrom(i,m_height-emptyLines-1)
			{
				test=false;
				break;
			}
	}

	// Daten neu speichern
	if(emptyLines>0)
	{
		int new_height=m_height-emptyLines;
		int new_length=new_height*m_width;
		char* tmp=new char[new_length];

		memcpy(tmp,m_data,new_length*sizeof(char));

		delete [] m_data;
		m_data=tmp;
		m_height=new_height;
		m_length=new_length;
	}
}
