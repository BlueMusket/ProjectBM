#pragma once

enum class PacketType
{
	DELAY = 0, // 패킷을 보낼때 지연 시킨다.
	NO_DELAY,  // 패킷을 보낼때 지연 시키지 않는다.

	COUNT,
};

class CPacketBase
{
public:
	CPacketBase() {};
	virtual ~CPacketBase() {};

public:
public:
	virtual uint8_t* Pack() = 0;
	virtual void UnPack(uint8_t* buffer) = 0;
};

#define PACKET_FOUNDATION(name, Type)\
public:\
	name() : CPacketBase() {} \
	virtual ~name() {} \
	static std::string	GetName() { return #name; }\
	static int			GetHash() { return std::hash<std::string>()(#name); }\
	static PacketType	GetType() { return Type; }
	

template <typename T>
struct IsPod { enum { Value = std::is_arithmetic<T>::value || std::is_enum<T>::value }; };

template <typename T>
void ConvertToBuffer(char* outBuffer, int size, T& value)
{
	char* buffer = new char[size];
	memcpy(buffer, &value, size);

	outBuffer = buffer;
}

//
//#define PACKET_BEGIN(name)\
//class name\
//{\
//public:\
//	static std::string	GetName() { return #name; }\
//	static int			GetHash() { return std::hash<std::string>()(#name); 
//
//
//#define PACKET_MEMBER( type, name )\
//	type name;\
//	void Set##name(type value ) { name = value; }\
//	type Get##name() const { return name; }\
//	const int GetBuffer()\
//	{\
//		if ( true == IsPod<type>::Value ) { return static_cast<int>(sizeof(type); }\
//		else { return type.GetByte(); }\
//	}
//
//#define PACKET_END \
//};\

//#pragma once
//
//#define PACKET_ENCRYPT_NONE 0
//#define PACKET_ENCRYPT_PLAIN 1
//#define PACKET_ENCRYPT_TENCENT 2
//
//struct YesType { enum { Value = true }; };
//struct NoType { enum { Value = false }; };
//
//template <typename T>
//struct IsPod { enum { Value = std::is_arithmetic<T>::value || std::is_enum<T>::value }; };
//
//template <typename T>
//struct MinBytes { enum { Value = sizeof(T) }; };
//
//template <typename T>
//struct MaxBytes { enum { Value = sizeof(T) }; };
//
//template <typename T, int T2>
//struct MaxBytesWithSize { enum { Value = sizeof(T) * T2 }; };
//
//template <typename T>
//struct FinalMaxBytes
//{
//	template <typename T, int ENCRYPTION>
//	struct MaxBytesImpl {};
//
//	template <typename T>
//	struct MaxBytesImpl<T, PACKET_ENCRYPT_NONE>
//	{
//		enum { Value = MaxBytes<T>::Value };
//	};
//
//	template <typename T>
//	struct MaxBytesImpl<T, PACKET_ENCRYPT_PLAIN>
//	{
//		enum { Value = MaxBytes<T>::Value };
//	};
//
//	template <typename T>
//	struct MaxBytesImpl<T, PACKET_ENCRYPT_TENCENT>
//	{
//		enum { Value = MaxBytes<T>::Value };
//	};
//
//	enum { Value = MaxBytesImpl<T, T::ENCRYPTION>::Value };
//};
//
//struct BytesCounter
//{
//public:
//	template <typename T>
//	static inline int Get(const T& value)
//	{
//		BytesImpl< IsPod<T>::Value > impl;
//		return impl(value);
//	};
//
//private:
//
//	template<bool IsPod>
//	struct BytesImpl {};
//
//	template<>
//	struct BytesImpl<true>
//	{
//		template <typename V>
//		inline int operator()(const V& value) const { return static_cast<int>(sizeof(V); }
//	};
//
//	template<>
//	struct BytesImpl<false>
//	{
//		template <typename V>
//		inline int operator()(const V& value) const { return value.Bytes(); }
//	};
//};
//
//class CRecvBuffer
//{
//private:
//	bool m_Malformed; // 패킷 변조
//	
//public:
//	CRecvBuffer() {}
//
//	virtual ~CRecvBuffer() {}
//
//public:
//	// 버퍼의 헤드를 움직이지 않고 주어진 길이만큼의 데이터를 읽어온다
//	virtual int Peek(char* outBuf, int len) = 0;
//	
//	// 주어진 길이만큼 버퍼 헤드를 뒤로 옮긴다
//	virtual int Skip(int len) = 0;
//
//	// 주어진 길이만큼 데이터를 읽어들인다.
//	virtual int ReadArray(char* outBuf, int len) = 0;
//
//public:
//
//	template <typename T>
//	inline int Read(T& value)
//	{
//		ReadImpl<IsPod<T>::Value> impl;
//		return impl(*this, value);
//	}
//
//private:
//	template<bool IsPod>
//	struct ReadImpl {};
//
//	template<>
//	struct ReadImpl<true>
//	{
//		template <typename V>
//		inline int operator()(CRecvBuffer& buffer, V& outValue) const 
//		{
//			return buffer.ReadArray(reinterpret_cast<char*>(&value), sizeof(V));
//		}
//	};
//
//	template<>
//	struct ReadImpl<false>
//	{
//		template <typename V>
//		inline int operator()(CRecvBuffer& buffer, const V& value) const 
//		{
//			return value.Read(buffer);
//		}
//	};
//};
//
//// 여기서 Proxy를 쓰는 이유
//// CRecvBuffer에 있는 기능 ( 템플릿 처리 ) 들을 직접적으로 보여주지 않기 위해
//class CRecvBufferProxy : public CRecvBuffer
//{
//private:
//	const char* m_Buffer; // 실제 버퍼 포인터
//	int m_MaxLength; // 버퍼의 최대 길이
//	int m_Offset; // 버퍼 헤드
//
//public:
//	CRecvBufferProxy(const char* buffer, int maxLength)
//		: m_Buffer(buffer), m_MaxLength(maxLength), m_Offset(0)
//	{}
//
//	virtual ~CRecvBufferProxy() {}
//
//public:
//	virtual int Peek(char* outBuf, int len) override
//	{
//		int read = 0;
//
//		if (0 < len)
//		{
//			if (m_Offset + len <= m_MaxLength)
//			{
//				memcpy(outBuf, m_Buffer + m_Offset, len);
//				read = len;
//			}
//		}
//
//		return read;
//	}
//
//	virtual int Skip(int len) override
//	{
//		int skipped = 0;
//		if (0 < len)
//		{
//			if (m_Offset + len <= m_MaxLength)
//			{
//				m_Offset += len;
//				skipped = len;
//			}
//		}
//
//		return skipped;
//	}
//
//	virtual int ReadArray(char* outBuf, int len) override
//	{
//		int read = 0;
//
//		if (0 < len)
//		{
//			if (m_Offset + len <= m_MaxLength)
//			{
//				memcpy(outBuf, m_Buffer + m_Offset, len);
//				m_Offset += len;
//				read = len;
//			}
//		}
//
//		return read;
//	}
//}
//
//struct CNewString
//{
//public:
//	std::wstring Value;
//	inline CNewString()
//	{
//		Value = L"";
//	}
//
//	inline CNewString(LPCTSTR value)
//	{
//		Value = value;
//	}
//
//	inline int Bytes() const
//	{
//		// 스트링 사이즈 + 스트링
//		return sizeof(short) + static_cast<int>((_tcslen(Value.c_str()) + 1) * sizeof(TCHAR));
//	}
//
//	inline int Read(CRecvBuffer& buf)
//	{
//		int read = 0;
//		Value = L"";
//
//		short len = 0;
//		read += buf.Read(len);
//
//		if (0 <= len)
//		{
//			TCHAR* readBuffer = new TCHAR[len + 1];
//			read += buf.ReadArray(reinterpret_cast<char*>(readBuffer), static_cast<int>(len + 1) * sizeof(TCHAR));
//			readBuffer[len] = 0;
//
//			Value = readBuffer;
//			delete readBuffer;
//		}
//		else
//		{
//			// 패킷 변조
//		}
//
//		return read;
//	}
//
//	inline int Write(CSendBuffer& buf) const
//	{
//		int written = 0;
//
//		short len = static_cast<short>(_tcslen(Value.c_str()));
//		written += buf.Write(len);
//		written += buf.WriteArray(reinterpret_cast<const char*>(Value.c_str()), static_cast<int>(len + 1) * sizeof(TCHAR));
//	}
//};
//
//template<>
//struct IsPod<CNewString> { enum { Value = NoType::Value }; };
//
//template<>
//struct MinBytes<CNewString> { enum { Value = sizeof(short) }; };
//
//template<>
//struct MaxBytes<CNewString> {};
//
//
//template<int T>
//struct MaxBytesWithSize<CNewString, T> { enum { Value = sizeof(short) + (sizeof(TCHAR) * (T + 1)) }; };
//
//
//template <typename T>
//struct CNewList
//{
//public:
//	std::vector<T> Elements;
//
//	inline CNewList()
//	{
//
//	}
//
//	template<class T>
//	CNewList(const T& rhs)
//	{
//		*this = rhs;
//	}
//
//	inline int Bytes() const
//	{
//		BytesImpl<IsPod<T>::Value> impl;
//		return impl(Elements, GetCount());
//	}
//
//	inline int Read(CRecvBuffer& buf)
//	{
//		ReadImpl<IsPod<T>::Value> impl;
//		return impl(buf, Elements);
//	}
//
//private:
//	template < bool IsPod>
//	struct BytesImpl {};
//
//	template<>
//	struct BytesImpl<true>
//	{
//		template <typename V>
//		inline int operator()(const std::vector<T>& element, short count ) const 
//		{
//			// 리스트 수 + 리스트 
//			return sizeof(count) + sizeof(T) * count;
//		}
//	};
//
//	template<>
//	struct BytesImpl<false>
//	{
//		template <typename V>
//		inline int operator()(const V& value) const 
//		{
//			int size = 0;
//			size += sizeof(count);
//
//			for (short i = 0; i < count; ++i)
//			{
//				size += elements[i].Bytes();
//			}
//
//			return size;
//		}
//	};
//
//
//	template<bool IsPod>
//	struct ReadImpl {};
//
//	template<>
//	struct ReadImpl<true>
//	{
//		template <typename V>
//		inline int operator()(CRecvBuffer& buffer, std::vector<T>& outElements) const
//		{
//			short count = 0;
//			int read = 0;
//
//			elements.clear();
//
//			read += buf.Read(count);
//
//			if (0 < count)
//			{
//				elements.reserve(count);
//				for (int i = 0 i < count; ++i)
//				{
//					elements.emplace_back();
//					read += buf.Read(elements[i]);
//				}
//			}
//			else if (count != 0)
//			{
//				count = 0;
//				// 변조 당함
//			}
//
//			return read;
//		}
//	};
//
//	template<>
//	struct ReadImpl<false>
//	{
//		template <typename V>
//		inline int operator()(CRecvBuffer& buffer, std::vector<T>& outElements) const
//		{
//			short count = 0;
//			int read = 0;
//
//			elements.clear();
//
//			read += buf.Read(count);
//
//			if (0 < count)
//			{
//				elements.reserve(count);
//				for (int i = 0 i < count; ++i)
//				{
//					elements.emplace_back();
//					read += buf.Read(elements[i]);
//				}
//			}
//			else if (count != 0)
//			{
//				count = 0;
//				// 변조 당함
//			}
//
//			return read;
//		}
//	};
//};
//
//
//template<typename T>
//struct IsPod<CNewList<T>> { enum { Value = NoType::Value }; };
//
//template<typename T>
//struct MinBytes<CNewList<T>> { enum { Value = sizeof(short) }; };
//
//template<typename T>
//struct MaxBytes<CNewList<T>> {};
//
//
//template<typename T, int T2>
//struct MaxBytesWithSize<CNewList<T>, T2> { enum { Value = sizeof(short) + MaxBytes<T>::Value * T2 }; };
//
//
//
//struct CChatData
//{
//	ChatType m_ChatType;
//	CNewString m_Message;
//
//	int Bytes() const
//	{
//		int size = 0;
//		size += BytesCounter::Get(m_ChatType);
//		size += BytesCounter::Get(m_Message);
//	}
//
//	int Read(CRecvBuffer& buf)
//	{
//		int read = 0;
//		read += buf.Read(m_ChatType);
//		read += buf.Read(m_Message);
//
//		return read;
//	}
//
//	int Write(CSendBuffer& buf) const
//	{
//		int written = 0;
//
//		written += buf.Write(m_ChatType);
//		written += buf.Write(m_Message);
//
//		return written;
//	}
//};
//
//template<> struct IsPod<CChatData> { enum { Value = NoType::Value }; };
//template<> struct MinBytes< CChatData> { enum { Value = MinBytes<ChatType>::Value + MinBytes<CNewString>::Value }; };
//template<> struct MaxBytes< CChatData> { enum { Value = MaxBytes<ChatType>::Value + MaxBytesWithSize<CNewString, 100>::Value }; };
