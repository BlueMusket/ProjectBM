#pragma once


class CObject;
typedef std::shared_ptr<CObject> CObjectPtr;
typedef std::weak_ptr<CObject> CObjectWeakPtr;

/// <summary>
/// 관리가 필요한 클래스의 부모 클래스
/// </summary>
class CObject
{
private:
	CAtomic<bool> m_IsDeleted;
	CObjectPtr m_Self;

public:
	CObject();
	virtual ~CObject();
public:
	template<typename T>
	std::shared_ptr<T> GetSelf() 
	{
		static_assert(std::is_base_of<CObject, T>::value, "T must be derived from CObject");
		return std::static_pointer_cast<T>(m_Self);
	}

	template<typename T>
	std::weak_ptr<T> GetWeakSelf() 
	{
		static_assert(std::is_base_of<CObject, T>::value, "T must be derived from CObject");
		return std::weak_ptr<T>(GetSelf<T>());
	}

public:
	bool IsDeleted() const { return m_IsDeleted; }

	void ReleaseSelf();

public:
	virtual bool CanDelete();
	static void SafeDelete(CObject* object);
};

// CObject 사용 예제
//{
//	std::weak_ptr<CPeer> weak;
//	{
//		std::shared_ptr<CPeer> same;
//		{
//			auto newPeer = New(CPeer); // 원본 생성 m_Self가 만들어 지면서 참조 카운트 1
//
//			same = newPeer->GetSelf<CPeer>(); // 원본으로 새로운 SharedPtr을 만들며 참조 카운트 2
//		}
//
//		CPeer* samePeer = nullptr;
//		{
//			weak = same->GetWeakSelf<CPeer>(); // weak 생성 참조 카운트 2
//
//			if (auto lockPtr = weak.lock()) // weak로 SharedPtr 생성 참조 카운트 3
//			{
//				samePeer = lockPtr.get();
//				same->ReleaseSelf(); // 여기서 포인터의 원본 SharedPtr 릴리즈, 참조 카운트 2
//			} // weakPtr 릴리즈, 참조 카운트 1
//		}
//	} // 여기서 same 릴리즈, 참조 카운트 0, SafeDelete호출
//
//	// 모든 자원이 소멸되어서 SharedPtr 생성 불가능
//	if (auto lockPtr = weak.lock())
//	{
//		lockPtr->GetId();
//	}
//}