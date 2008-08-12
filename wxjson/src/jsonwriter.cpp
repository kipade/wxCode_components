/////////////////////////////////////////////////////////////////////////////
// Name:        jsonwriter.cpp
// Purpose:     the wxJSONWriter class: a JSON text generator
// Author:      Luciano Cattani
// Created:     2007/10/12
// RCS-ID:      $Id: jsonwriter.cpp,v 1.6 2008/03/03 19:05:47 luccat Exp $
// Copyright:   (c) 2007 Luciano Cattani
// Licence:     wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
    #pragma implementation "jsonwriter.cpp"
#endif


#include <wx/jsonwriter.h>

#include <wx/sstream.h>
#include <wx/debug.h>
#include <wx/log.h>

static const wxChar* writerTraceMask = _T("traceWriter");

/*! \class wxJSONWriter
 \brief The JSON document writer

 This class is a JSON document writer and it is used to write a
 wxJSONValue object to an output stream or to a string object
 of type wxString.
 The ctor accepts some parameters which can be used to 
 change the style of the output.
 The default output is in human-readable format.

 Here is an example on how to use this class:

 \code
   // construct the JSON value object and add values to it
   wxJSONValue root;
   root["key1"] = "some value";
   ...

   // now we want a string that contains the text data
   // we use the default settings to obtain human-readable text
   wxJSONWriter jsw;
   wxString     str;
   jsw.Write( root, str );
 \endcode

 \par output objects

 You can write JSON text to two different kind of objects:

 \li a string object (\b wxString)
 \li a stream object (\b wxOutputStream)

 When writing to a string object, the output is platform dependent.
 In ANSI builds, the JSON text output in the string object will
 contain one-byte characters: the actual characters represented is
 locale dependent.
 In Unicode builds, the JSON text output in the string contains
 wide characters which encoding format is platform dependent: UCS-2 in
 Windows, UCS-4 in GNU/Linux.

 When writing to a stream object, the JSON text output is always
 encoded in UTF-8 in both ANSI and Unicode builds.

 For more info about the unicode topic see \ref wxjson_tutorial_unicode.
*/

//! Ctor.
/*!
 Construct the JSON writer object with the specified parameters.
 Note that if \c styled is FALSE the indentation is totally suppressed
 and the values of the other two parameters are simply ignored.

 \param indent the initial indentation in number of spaces. Default is ZERO.
	If you specify the wxJSONWRITER_TAB_INDENT flag for the \e style,
	this value referes to the number of TABs in the initial indentation

 \param step the indentation increment for new objects/arrays in number of spaces
	 (default is 3).
	If you specify the wxJSONWRITER_TAB_INDENT flag for the \e style,
	this value ignored: the indentation increment is only one TAB character.

 \param style this can be a combination of the following constant OR'ed togheter:
	\li wxJSONWRITER_NONE: no indentation is performed (hard to read by humans)
			and no comment lines are written.
	\li wxJSONWRITER_STYLED: output is human-readable (indented)
	\li wxJSONWRITER_WRITE_COMMENTS:
	this flag force the writer to write C/C++ comment strings: the comments
	will be written in their original position. Specifying this flag also
	implies the wxJSONWRITER_STYLED flag to be automatically set.
	\li wxJSONWRITER_COMMENTS_BEFORE: this flag force the writer to write C/C++ comments
	always before the value they refer to.
	Specifying this flag also implies the wxJSONWRITER_STYLED and
	wxJSONWRITER_WRITE_COMMENTS flags to be	automatically set.
	\li wxJSONWRITER_COMMENTS_AFTER: this flag force the writer to write C/C++ comments
	always after the value they refer to.
	Specifying this flag also implies the wxJSONWRITER_STYLED and
	wxJSONWRITER_WRITE_COMMENTS flags to be	automatically set.
	\li wxJSONWRITER_SPLIT_STRINGS: this flag force the writer to split string
	values into two or more lines if they contain a new-line character.
	Specifying this flag also implies the wxJSONWRITER_STYLED flag to be
	automatically set.
	See \ref json_multiline_string for more info.
	\li wxJSONWRITER_NO_LINEFEEDS: this flag cause the JSON writer to not add
	new-lines between values
	\li wxJSONWRITER_ESCAPE_SOLIDUS: the solidus character (/) should only be
	escaped if the JSON text is meant for embedding in HTML.
	Unlike in older 0.x versions, it is disabled by default and this flag cause
	the solidus char to be escaped.
	\li wxJSONWRITER_MULTILINE_STRING:this is a multiline-string mode where newlines
	and tabs are not escaped. This is not strict JSON, but it helps immensely when
	manually editing json files with multiline strings
	\li wxJSONWRITER_RECOGNIZE_UNSIGNED: this flag cause the JSON writer to prepend
	a plus sign (+) to unsigned integer values. This is used by the wxJSON reader to
	force the integer to be stored in an \b unsigned \b int. Note that this
	feature may be incompatible with other JSON implementations.
	\li wxJSONWRITER_TAB_INDENT: this flag cause the indentation of sub-objects / arrays
	to be done using a TAB character instead of SPACES.
	Specifying this flag also implies the wxJSONWRITER_STYLED flag to be
	automatically set.


 Note that some flags depends on other flags: for example, all comment-related
 flags depend on the \e styled flag (wxJSONWRITER_STYLED)..
 In other words, if you want comments to be written to the JSON text both the
 wxJSONWRITER_WRITE_COMMENTS \b and wxJSONWRITER_STYLED flags must be set.

 Unlike in older 0.x versions, all flags that depend on other flags cause the
 dependant flag to be set automatically. This is compatible with the past: old
 applications can specify all necessary flags.

 You have to note that the wxJSONWRITER_NO_LINEFEEDS flag is incompatible with
 comments and with the multiline-string flag.
 This is because C++ comments ends when a LF character is encontered and the
 wxJSONWRITER_MULTILINE_STRING cause the LF char to not being escaped

 \b Examples

 To write a JSON value object using a four-spaces indentation and forcing all
 comment strings to apear before the value they refer to, use the following code:
 \code
  wxJSONWriter writer( wxJSONWRITER_STYLED |   // want a styled output
                wxJSONWRITER_WRITE_COMMENTS |  // want comments in the document
                wxJSONWRITER_COMMENTS_BEFORE,  // force comments before value
                0,                             // initial indentation
                4);                            // indentation step
  writer.Write( value, document );

  // in the new 1.0 version, you can get the same result using the
  // following construct

  wxJSONWriter writer( 
		wxJSONWRITER_COMMENTS_BEFORE,  // the other flags are set automatically
                0,                             // initial indentation
                4);                            // indentation step
  writer.Write( value, document );
 \endcode

 The following code construct a JSON writer that produces hard-to-read
 output: indentation is suppressed and no comment lines are written
 and the values in the JSON text are not separated by LF

 \code
  wxJSONWriter writer( wxJSONWRITER_NO_LINEFEEDS );
  writer.Write( value, document );
 \endcode

*/
wxJSONWriter::wxJSONWriter( int style, int indent, int step )
{
  m_indent = indent;
  m_step   = step;
  m_style  = style;
  if ( m_style == wxJSONWRITER_NONE )  {
    m_indent = 0;
    m_step   = 0;
  }
}

//! Dtor - does nothing
wxJSONWriter::~wxJSONWriter()
{
}

//! Write the JSONvalue object to a JSON text.
/*!
 The two overloaded versions of this function let the user choose
 the output object which can be:

 \li a string object (\b wxString)
 \li a stream object ( \b wxOutputStream)

 The two types of output object are very different because the
 text outputted in encoded in different formats depending on the
 build mode.

 For \b Unicode builds, the JSON text output is platform dependent
 because \b wxString objects store wide characters which are
 represented in different formats: UCS-2 on Windows and UCS-4
 on Linux.

 For \b ANSI mode the JSON text output written to a string object
 is encoded in a locale dependent format: wide characters are not
 supported and the string object always contains one-byte characters.

 When the output object is a stream, the JSON text output is always
 encoded in UTF-8 format in both Unicode and ANSI builds.

 Also note that the Write() function does not return a status code.
 If you are writing to a string, you do not have to warry about this
 issue: no errors can occur when writing to strings.
 On the other hand, wehn writing to a stream there could be errors
 in the write operation.
 If an error occurs, the \c Write(9 function immediatly returns
 without trying further output operations.
 You have to check the status of the stream by calling the stream's
 memberfunctions. Example:

 \code
   // construct the JSON value object and add values to it
   wxJSONValue root;
   root["key1"] = "some value";

   // write to a stream
   wxMemoryOutputStream mem;
   wxJSONWriter writer;
   writer.Write( root, mem );
   wxStreamError err = mem.GetLastError();
   if ( err != wxSTREAM_NO_ERROR )  {
     MessageBox( _T("ERROR: cannot write the JSON text output"));
   }
\endcode
*/
void
wxJSONWriter::Write( const wxJSONValue& value, wxString& str )
{
  m_level = 0;

  // when writing to string objects, we cannot use different charsets
  // as the one used in the wxString object which is either ANSI or
  // Unicode depending the wxWidget's build mode.
  m_conv  = 0;

  m_outType   = 0;      // string
  m_outObject = &str;
  DoWrite( value, 0, false );
}

//! \overload Write( const wxJSONValue&, wxString& )
void
wxJSONWriter::Write( const wxJSONValue& value, wxOutputStream& os )
{
  m_level = 0;
  // we use the UTF-8 encoding. It is only meaningfull in Unicode builds
  wxMBConvUTF8 conv;
  m_conv  = &conv;

  m_outType   = 1;      // stream
  m_outObject = &os;

  DoWrite( value, 0, false );
}


//! Perform the real write operation.
/*!
 This is a recursive function. If the value is not a hashmap or
 an array, the function calls the other \b WriteXxxxx functions
 which actually write the text output.
 For maps and arrays, the function calls itself for all items
 in the array / hashmap after incrementing the \c m_level data member.
*/
int
wxJSONWriter::DoWrite( const wxJSONValue& value, const wxString* key,
				bool comma )
{
  // note that this function is recursive

  // some variables that cannot be allocated in the switch statement
  const wxJSONInternalMap* map = 0;
  int size;

  // determine the comment position; it is one of:
  //
  //  wxJSONVALUE_COMMENT_BEFORE
  //  wxJSONVALUE_COMMENT_AFTER
  //  wxJSONVALUE_COMMENT_INLINE
  //
  // or -1 if comments have not to be written
  int commentPos = -1;
  if ( value.GetCommentCount() > 0 && (m_style & wxJSONWRITER_WRITE_COMMENTS))  {
    commentPos = value.GetCommentPos();
    if ( ( m_style & wxJSONWRITER_COMMENTS_BEFORE) != 0 ) {
      commentPos = wxJSONVALUE_COMMENT_BEFORE;
    }
    else if ( (m_style & wxJSONWRITER_COMMENTS_AFTER) != 0 ) {
      commentPos = wxJSONVALUE_COMMENT_AFTER;
    }
  }

  int lastChar = 0;  // check if WriteComment() writes the last LF char

  // first write the comment if it is BEFORE
  if ( commentPos == wxJSONVALUE_COMMENT_BEFORE )   {
    lastChar = WriteComment( value, true );
  }
  if ( lastChar < 0 )   {
    return lastChar;
  }

  lastChar = WriteIndent();
  if ( lastChar < 0 )   {
    return lastChar;
  }

  // now write the key if it is not NULL
  if ( key )   {
    lastChar = WriteKey( *key );
  }
  if ( lastChar < 0 )   {
    return lastChar;
  }

  // now write the value
  wxJSONInternalMap::const_iterator it; 
  long int count = 0;

  wxJSONType t = value.GetType();
  switch ( t )  {
    case wxJSONTYPE_INVALID :
      WriteInvalid();
      wxFAIL_MSG( _T("wxJSONWriter::WriteEmpty() cannot be called (not a valid JSON text"));
      break;

    case wxJSONTYPE_INT :
    case wxJSONTYPE_SHORT :
    case wxJSONTYPE_LONG :
    case wxJSONTYPE_INT64 :
      lastChar = WritePrimitiveValue( value );
      break;

    case wxJSONTYPE_UINT :
    case wxJSONTYPE_USHORT :
    case wxJSONTYPE_ULONG :
    case wxJSONTYPE_UINT64 :
      // prepend a plus sign if the style specifies that unsigned integers
      // have to be recognized by the JSON reader
      if ( m_style & wxJSONWRITER_RECOGNIZE_UNSIGNED )  {
        lastChar = WriteChar( '+' );
      }
      lastChar = WritePrimitiveValue( value );
      break;

    case wxJSONTYPE_NULL :
    case wxJSONTYPE_BOOL :
    case wxJSONTYPE_DOUBLE :
      lastChar = WritePrimitiveValue( value );
      break;

    case wxJSONTYPE_STRING :
      lastChar = WriteStringValue( value.AsString());
      break;

    case wxJSONTYPE_CSTRING :
      // we use the 'WriteString()' function
      lastChar = WriteStringValue( value.AsString());
      break;

    case wxJSONTYPE_ARRAY :
      ++m_level;
      lastChar = WriteChar( '[' );
      // the inline comment for objects and arrays are printed in the open char
      if ( commentPos == wxJSONVALUE_COMMENT_INLINE )   {
        commentPos = -1;  // we have already written the comment
        lastChar = WriteChar( ' ' );
        if ( lastChar < 0 )   {
          return lastChar;
        }
        lastChar = WriteComment( value, false );
        if ( lastChar < 0 )   {
          return lastChar;
        }
        if ( lastChar != '\n' )   {
          WriteChar( '\n' );
          lastChar = '\n';
        }
      }
      else   {
        lastChar = WriteChar( '\n' );
        if ( lastChar < 0 )   {
          return lastChar;
        }
      }

      size = value.Size();
      for ( int i = 0; i < size; i++ )  {
        bool comma = false;
        if ( i < size - 1 )  {
          comma = true;
        }
        wxJSONValue v = value.ItemAt( i );
        lastChar = DoWrite( v, 0, comma );
        if ( lastChar == -1 )  {
          return lastChar;
        }
      }
      --m_level;
      lastChar = WriteIndent();
      if ( lastChar < 0 )   {
        return lastChar;
      }
      lastChar = WriteChar( ']' );
      break;

    case wxJSONTYPE_OBJECT :
      ++m_level;

      lastChar = WriteChar( '{' );
      if ( lastChar < 0 )   {
        return lastChar;
      }
      // the inline comment for objects and arrays are printed in the open char
      if ( commentPos == wxJSONVALUE_COMMENT_INLINE )   {
        lastChar = WriteChar( ' ' );
        commentPos = -1;  // we have already written the comment
        lastChar = WriteComment( value, false );
        if ( lastChar < 0 )   {
          return lastChar;
        }
        if ( lastChar != '\n' )   {
          WriteChar( '\n' );
        }
      }
      else   {
        lastChar = WriteChar( '\n' );
      }

      map = value.AsMap();
      size = value.Size();
      count = 0;
      for ( it = map->begin(); it != map->end(); ++it )  {
        // get the key and the value
        wxString key = it->first;
        const wxJSONValue& v = it->second;

        bool comma = false;
        if ( count < (size - 1) )  {
          comma = true;
        }
        lastChar = DoWrite( v, &key, comma );
        if ( lastChar == -1 )  {
          return lastChar;
        }
        count++;
      }
      --m_level;
      lastChar = WriteIndent();
      if ( lastChar < 0 )   {
        return lastChar;
      }
      lastChar = WriteChar( '}' );
      break;

    default :
      // a not yet defined wxJSONType: let's call WritePrimitiveValue()
      // which writes the string returned by wxJSONVal::AsString() function;
      lastChar = WritePrimitiveValue( value );
      break;

  }

  // when the value is written, check if we need a comma character
  // and if a comment inline / after must be written
  if ( comma )   {
    lastChar = WriteChar( ',' );
    if ( lastChar < 0 )   {
      return lastChar;
    }
  }
  if ( commentPos == wxJSONVALUE_COMMENT_INLINE )   {
    lastChar = WriteChar( ' ' );
    lastChar = WriteComment( value, false );
    if ( lastChar < 0 )   {
      return lastChar;
    }
  }
  else if ( commentPos == wxJSONVALUE_COMMENT_AFTER )   {
    WriteChar( '\n' );
    lastChar = WriteComment( value, true );
    if ( lastChar < 0 )   {
      return lastChar;
    }
  }
  if ( lastChar != '\n' )  {
    lastChar = WriteChar( '\n' );
  }
  return lastChar;
}


//! Write the comment strings, if any.
int
wxJSONWriter::WriteComment( const wxJSONValue& value, bool indent )
{
  // the function returns the last character written which should be
  // a LF char or -1 in case of errors
  // if nothing is written, returns ZERO
  int lastChar = 0;

  // only write comments if the style is STYLED and the WRITE_COMMENTS flag
  // is set.
  if ( (m_style & wxJSONWRITER_STYLED ) == 0 ) {
    return lastChar;
  }
  if ( (m_style & wxJSONWRITER_WRITE_COMMENTS ) == 0 ) {
    return lastChar;
  }

  const wxArrayString cmt = value.GetCommentArray();
  int cmtSize = cmt.GetCount();
  for ( int i = 0; i < cmtSize; i++ )    {
    if ( indent )  {
      lastChar = WriteIndent();
    }
    WriteString( cmt[i]);
    lastChar = cmt[i].Last();
    if ( lastChar != '\n' )   {
      lastChar = WriteChar( '\n' );
    }
  }
  return lastChar;
}

//! Writes the indentation to the JSON text.
/*!
 The two functions write the indentation as \e spaces in the JSON output
 text. When called with a int parameter, the function
 writes the specified number of spaces.
 If no parameter is given, the function computes the number of spaces
 using the following formula:
 \code
  numSpaces = m_indent + ( m_step * m_level )
 \endcode
*/
int
wxJSONWriter::WriteIndent()
{
  int lastChar = 0;
  if ( m_style & wxJSONWRITER_TAB_INDENT ) {
    lastChar = WriteTabIndent();
  }
  else {
    int numSpaces = m_indent + ( m_step * m_level );
    if ( m_style & wxJSONWRITER_STYLED )  {
      for ( int i = 0; i < numSpaces; i++ )  {
        lastChar = WriteChar( ' ' );
        if ( lastChar == -1 )  {
          break;
        }
      }
    }
  }
  return lastChar;
}

//! \overload WriteIndent()
int
wxJSONWriter::WriteIndent( int num )
{
  int lastChar = 0;
  if ( m_style & wxJSONWRITER_STYLED )  {
    for ( int i = 0; i < num; i++ )  {
      lastChar = WriteChar( ' ' );
      if ( lastChar == -1 )  {
        break;
      }
    }
  }
  return lastChar;
}

//! Writes the indentation to the JSON text.
/*!
 The function is called by \c WriteIndent when the writer object was
 constructed using the wxJSONWRITER_TAB_INDENT which cause indentation
 to be done using TAB characters instead of a variable number of spaces.

 The function computes the number of TAB of indentation using thefollowing formula:
 \code
  numTabs = m_indent + m_level
 \endcode
*/
int
wxJSONWriter::WriteTabIndent()
{
  int lastChar = 0;
  int numTabs = m_indent + m_level;
  if ( m_style & wxJSONWRITER_STYLED )  {
    for ( int i = 0; i < numTabs; i++ )  {
      lastChar = WriteChar( '\t' );
      if ( lastChar == -1 )  {
        break;
      }
    }
  }
  return lastChar;
}

//! Write the provided string to the output object.
/*!
 The function writes the string \c str to the output object that
 was specified in the wxJSONWriter::Write() function.
 The function may split strings in two or more lines if the
 string contains LF characters if the \c m_style data member contains
 the wxJSONWRITER_SPLIT_STRING flag.

 The function does not actually write the string: for every character
 in the provided string the function calls WriteChar() which does
 the actual character output.

 The function returns the last character written or -1 in case of errors. 
*/
int
wxJSONWriter::WriteStringValue( const wxString& str )
{

  // the 'multiLineIndent' variable controls
  // the output and indentation of multiline strings
  // it would be nice if the lines after the first one start at the same
  // column as, for example:
  //
  //    "key" : "this is first line\n"
  //            "this is line #2\n"
  //            "this is line #3"
  //
  // but there is not a data member that stores the actual column number
  // so by now, the indentation is calculated by adding 2 levels to the
  // current level number so the output of the above example will be
  // (consider a indent step of 3 (the default):
  //
  //    "key" : "this is first line\n"
  //          "this is line #2\n"
  //          "this is line #3"
  //
  int multiLineIndent = -1;
  if ( ( m_style & wxJSONWRITER_SPLIT_STRING) && ( m_style & wxJSONWRITER_STYLED) )   {
    multiLineIndent = ( m_level + 2 ) * m_step;
  }

  int lastChar = WriteChar( '\"' );  // open quotes
  if ( lastChar < 0 )   {
    return lastChar;
  }

  // every character is written using the WriteChar() function
  // for every character we have to check if it is a character that
  // needs to be escaped: note that characters that should be escaped
  // may be not if some writer's flags are specified
  size_t len = str.length();
  for ( size_t i = 0; i < len; i++ ) {
    bool shouldEscape = false;
    wxChar ch = str.at(i );
    switch ( ch )  {
      case '\"' :     // quotes
        shouldEscape = true;
        break;
      case '\\' :     // reverse solidus
        shouldEscape = true;
        break;
      case '/'  :     // solidus
        if ( m_style & wxJSONWRITER_ESCAPE_SOLIDUS )  {
          shouldEscape = true;
        }
        break;
      case '\b' :     // backspace
        shouldEscape = true;
        break;
      case '\f' :     // formfeed
        shouldEscape = true;
        break;
      case '\n' :     // newline
        if ( m_style & wxJSONWRITER_MULTILINE_STRING )  {
          shouldEscape = false;
        }
        else {
          shouldEscape = true;
        }
        break;
      case '\r' :     // carriage-return
        shouldEscape = true;
        break;
      case '\t' :      // horizontal tab
        if ( m_style & wxJSONWRITER_MULTILINE_STRING )  {
          shouldEscape = false;
        }
        else {
          shouldEscape = true;
        }
        break;
      default :
          shouldEscape = false;
        break;
    }

    // before writing the character, write the ESC if it should be escaped
    if ( shouldEscape )  {
      lastChar = WriteChar( '\\' );
      if ( lastChar < 0 )  {
        return lastChar;
      }
    }

    // now write the character
    lastChar = WriteChar( ch );
    if ( lastChar < 0 )  {
      return lastChar;
    }

    // check if the char is LF and if the style is SPLIT_STRING
    if ( ch == '\n' && multiLineIndent > 0 )   {
      lastChar = WriteString( _T("\"\n" ));       // close quotes and CR
      if ( lastChar < 0 )  {
        return lastChar;
      }
      lastChar = WriteIndent( multiLineIndent ); // write indentation
      if ( lastChar < 0 )  {
        return lastChar;
      }
      lastChar = WriteChar( '\"' );              // reopen quotes
      if ( lastChar < 0 )  {
        return lastChar;
      }
    }
  }
  lastChar = WriteChar( '\"' );  // close quotes
  return lastChar;
}

//! Write a character to the output object
/*!
 This function does the real output of the JSON text to the output
 object which can be a wxString object or a wxOutputStream object.
 The function outputs only one character.
 What is actually written to the output JSON text depends on:

 \li if the output is a string object, the function just appends
	to the string object pointed to by \c m_outObject the
	character that has to be written

 \li if the output is a stream object than we have to distinguish
	if the library has built in ANSI or Unicode mode:

	\li in ANSI builds, the character is converted to a wide
		character and then to UTF-8 encoding format
	\li in Unicode builds, the wide character is converted to
		UTF-8 format

 The function returns the written character ('ch' itself) or -1 in case
 of errors.
*/
int
wxJSONWriter::WriteChar( wxChar ch )
{
  // we have to set the result 'r' equal to the returned char
  // but ANSI and Unicode are different - see the Test60() function
  // in 'samples/test13.cpp' source file.
#if defined( wxJSON_USE_UNICODE )
  int r = ch;
#else
  int r = (unsigned char) ch;
#endif

  if(m_style & wxJSONWRITER_NO_LINEFEEDS && wxChar('\n') == ch) {
    return r;	//	style specifies not to include line feeds
  }

  if ( m_outType == 0 )  {   // output is a string object?
    //wxString* out = wxDynamicCast( m_outObject, wxString );
    //wxJSON_ASSERT( out != 0 );
    wxString* out = (wxString*) m_outObject;
    out->append( ch );
  }
  else  {                   // output is a stream
    //wxOutputStream* out = wxDynamicCast( m_outObject, wxOutputStream );
    //wxJSON_ASSERT( out != 0 );
    wxOutputStream* out = (wxOutputStream*) m_outObject;
    wchar_t wchar[2]; size_t len;

#if !defined( wxJSON_USE_UNICODE )
    // in ANSI builds we have to first convert the locale dependent
    // character to a wide char
    char    c = (char) ch;
    len = wxConvLibc.ToWChar( wchar, 2, &c, 1 );
#else
    wchar[0] = ch;
#endif
    // writing to a stream is always done in UTF-8 format
    // the m_conv data member must contain a pointer to an instance
    // of a wxMBConvUTF8 class which is, by default, wxConvLocal

    char buffer[10];
    wxJSON_ASSERT( m_conv != 0 );

    len = m_conv->FromWChar( buffer, 10, &(wchar[0]), 1 );
    wxJSON_ASSERT( len != wxCONV_FAILED );

    // conversion is OK, write the buffer
    // it seems that the conversion function adds a trailing NULL byte
    // to the output buffer so we have to decrement the converted lenght by 1
    // see the Test37() function in 'samples/test9.cpp' for details

    ::wxLogTrace( writerTraceMask, _T("(%s) length=%d"), __PRETTY_FUNCTION__, (int) len );
    if ( len <= 1  )   {
      ::wxLogTrace( writerTraceMask,
		_T("(%s) length less than or equal to 1"), __PRETTY_FUNCTION__ );
    }

    wxJSON_ASSERT( len > 1 );
    out->Write( buffer, len - 1 );
    wxStreamError err = out->GetLastError();
    switch ( err )  {
      case wxSTREAM_NO_ERROR :
        break;
      case wxSTREAM_EOF :
        r = -1;
        break;
      case wxSTREAM_WRITE_ERROR :
      case wxSTREAM_READ_ERROR :
        r = -1;
        break;
      default :   // should never happen
        break;
    }
  }
  return r;
}

//! Write a generic string
/*!
 The function writes the wxString object \c str to the output object.
 The string is written as is; you cannot use it to write JSON strings
 to the output text.
 The function is used by many other functions for example by WriteInt()
 which converts the integer in a string and then writes it to the
 output JSON text.
 The function just calls WriteChar() for every character in the string.
*/
int
wxJSONWriter::WriteString( const wxString& str )
{
  ::wxLogTrace( writerTraceMask, _T("(%s) string to write=%s"),
				  __PRETTY_FUNCTION__, str.c_str() );

  int lastChar = 0;
  size_t len = str.length();
  for ( size_t i = 0; i < len; i++ ) {
    lastChar = WriteChar( str[i] );
    if ( lastChar < 0 )  {
      break;
    }
  }
  ::wxLogTrace( writerTraceMask, _T("(%s) result=%d"),
				  __PRETTY_FUNCTION__, lastChar );
  return lastChar;
}

//! Writes a value of primitive type.
/*!
 This function is called for every value object of primitive types
 except string values and it relaces all \c WriteXxxxx() functions.
 In order to write primitive types, this functions calls the
 wxJSONValue::AsString() function to get a string representation
 of the value.
 This function is called for values of type:
 \li wxJSONTYPE_NULL
 \li wxJSONTYPE_INT, LONG, SHORT, INT64
 \li wxJSONTYPE_UINT, ULONG, USHORT, UINT64
 \li wxJSONTYPE_DOUBLE
 \li wxJSONTYPE_BOOL

*/
int
wxJSONWriter::WritePrimitiveValue( const wxJSONValue& value )
{
  int r;
  wxString s = value.AsString();
  ::wxLogTrace( writerTraceMask, _T("(%s) value.AsString()=%s"),
				  __PRETTY_FUNCTION__, s.c_str() );

  wxJSON_ASSERT( !s.empty());
  r =  WriteString( s );
  return r;
}


//! Write the key of a key/value element to the output stream.
int
wxJSONWriter::WriteKey( const wxString& key )
{
 ::wxLogTrace( writerTraceMask, _T("(%s) key write=%s"),
				  __PRETTY_FUNCTION__, key.c_str() );

  WriteStringValue( key );
  wxString s( _T( " : " ));
  return WriteString( s );
}

//! Write the invalid JSON value to the output stream.
/*!
 An invalid wxJSONValue is a value that was not initialized and it is
 an error. You should not write empty values to JSON text because
 the output is not valid JSON text.
 Note that the NULL value is a legal JSON text and it is written:
 \code
  null
 \endcode

 This function writes a non-JSON text to the output stream:
 \code
  <invalid>
 \endcode
 In debug mode, the function always fails with an wxFAIL_MSG failure.
*/
int
wxJSONWriter::WriteInvalid()
{
  wxFAIL_MSG( _T("wxJSONWriter::WriteEmpty() cannot be called (not a valid JSON text"));
  wxString s( _T( "<empty>" ));
  return WriteString( s );
}

//! Writes an error string to the output JSON text (not used)
/*!
 The function just writes the provided string prepended with
 the \b ERROR word.
*/
int
wxJSONWriter::WriteError( const wxString& err )
{
  wxString s( _T( "ERROR: "));
  s.append( err );
  return WriteString( s );
}


/*
{
}
*/

