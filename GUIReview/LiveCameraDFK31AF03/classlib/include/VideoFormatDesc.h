
#ifndef _VIDEOFORMATDESC_H_
#define _VIDEOFORMATDESC_H_

#include "VideoFormatItem.h"

#include "int_interface_pre.h"

namespace _DSHOWLIB_NAMESPACE
{
	class Grabber;

	class _UDSHL_EXP_API VideoFormatDesc
	{
		friend class Grabber;
	public:
		~VideoFormatDesc();
	public:
		VideoFormatItem	createVideoFormat( SIZE size ) const;
		VideoFormatItem	createVideoFormat( int width, int height ) const;
	public:
		GUID			getSubtype() const;
		SIZE			getMinSize() const;
		SIZE			getMaxSize() const;
		SIZE			getStepSize() const;
		int				getBinningFactor() const;
		bool			isROIFormat() const;

		bool			isValidSize( const SIZE& sz ) const;

		/** get string representing this format desc
		 **/
		std::string		toString() const;
		std::wstring	toStringW() const;

		/** get string representing the color format of this format
		 * @return string representing the color format of this format
		 **/
		std::string		getColorformatString() const;
		std::wstring	getColorformatStringW() const;
	private:
		VideoFormatDesc( const VideoFormatDesc& op2 );					// noncopyable
		VideoFormatDesc&	operator=( const VideoFormatDesc& op2 );	// noncopyable

		VideoFormatDesc( const win32_utils::CVideoFormatDesc& desc, int binningFactor, bool isROIFormat );

		win32_utils::CVideoFormatDesc* m_pDesc;

		int		m_binningFactor;
		bool	m_isROIFormat;
	};

}

#endif // _VIDEOFORMATDESC_H_
