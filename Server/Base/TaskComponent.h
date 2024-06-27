#pragma once
#include "Component.h"

class CTaskComponent : public CComponent
{
	COMPONENT_FOUNDATION(CTaskComponent)

private:

};
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// \file AssetTask.h
///// \author excel96
///// \date 2015.11.5
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//#pragma once
//
//#include "Base/AsyncEvent.h"
//
//namespace Asset
//{
//    //------------------------------------------------------------------------------------------------------------------
//
//    // 실행 파일 타입
//    enum ExeType
//    {
//        ET_GAME = 0x00000001, ///< 게임 서버
//        ET_LOGIN = 0x00000002, ///< 로그인 서버
//        ET_WORLD = 0x00000004, ///< 월드 서버
//        ET_SOCIAL = 0x00000008, ///< 소셜 서버
//        ET_QUERY = 0x00000010, ///< 쿼리 서버
//        ET_CENTER = 0x00000020, ///< 센터 서버
//        ET_MATCH = 0x00000040, ///< 매치 서버
//        ET_AUCTION = 0x00000080, ///< 옥션 서버
//        ET_TRACE = 0x00000100, ///< 로그 서버
//        ET_FAM = 0x00000200, ///< 팸 서버
//        ET_DOCK = 0x00000400, ///< 독 서버
//        ET_ASSET = 0x00010000, ///< 애셋 마스터
//        ET_DUMMY = 0x00020000, ///< 더미 클라이언트
//        ET_SIMPLE = 0x00040000, ///< 심플 클라이언트
//        ET_ALL = 0xFFFFFFFF, ///< 모두 
//    };
//
//    //------------------------------------------------------------------------------------------------------------------
//
//    // 특정 애셋만 로드하기를 처리하기 위한 애셋 이름 셋
//    class CAssetNameSet
//    {
//    private:
//        stx::set<tstring, Text::LexLess> m_NameSet; ///< 애셋 목록
//
//
//    public:
//        /// \brief 생성자
//        CAssetNameSet();
//
//        /// \brief 생성자
//        CAssetNameSet(LPCTSTR text);
//        CAssetNameSet(const tstring& text);
//
//        /// \brief 소멸자
//        ~CAssetNameSet();
//
//
//    public:
//        /// \brief 추가
//        void Add(LPCTSTR name);
//        void Add(const tstring& name);
//
//        /// \brief 비어있나?
//        bool IsEmpty() const;
//
//        /// \brief 개수 반환
//        size_t GetCount() const;
//
//        /// \brief 리로드할 대상인가?
//        bool IsMatch(LPCTSTR name) const;
//        bool IsMatch(const tstring& name) const;
//
//        /// \brief 문자열 정보를 반환한다.
//        tstring ToString() const;
//    };
//
//    //------------------------------------------------------------------------------------------------------------------
//
//    // 리로드 중에 상태 표시를 위해 실행할 콜백
//    typedef Delegate::Delegate2<void, int, int> CAssetProgressCallback;
//
//    // 리로드 완료 후 실행할 콜백
//    typedef Delegate::Delegate1<void, const CAssetNameSet&> CAssetFinishCallback;
//
//    //------------------------------------------------------------------------------------------------------------------
//
//    /// \brief 애셋 로딩용 태스크 객체
//    class CTask :
//        public CAsyncEvent,
//        public CCountable<CTask>
//    {
//    public:
//        typedef std::function<void()> Callback;
//
//
//    private:
//        Callback m_Callback; ///< 호출할 함수
//
//        static CAtomic<int> s_PendingCount; ///< 아직 처리되지 않은 태스크 객체의 수
//
//
//    public:
//        /// \brief 생성자
//        CTask(const Callback& callback);
//
//        /// \brief 소멸자
//        virtual ~CTask();
//
//
//    public:
//        /// \brief 이벤트의 내용을 실행한다.
//        virtual void Execute(bool success, DWORD transferred, CAsyncEventSink* sink) override;
//
//
//    public:
//        /// \brief 태스크를 포스트한다.
//        static void PostTask(CTask* task);
//
//        /// \brief 아직 처리되지 않은 태스크의 수를 반환한다.
//        static int GetPendingCount();
//    };
//
//    //------------------------------------------------------------------------------------------------------------------
//
//    void WaitAll();
//
//    /// \brief 주어진 함수자를 포스트
//    template <typename Functor>
//    inline void Post(const Functor& func)
//    {
//        CTask::PostTask(xnew(CTask, func));
//    }
//
//    /// \brief 호출자가 해당 사항 있는 넘이라면 주어진 함수자를 포스트
//    template <typename Functor>
//    inline void Post(LPCTSTR name, const Functor& func, ExeType exe, const CAssetNameSet& wanted, int flag)
//    {
//        if ((flag & exe) != 0)
//        {
//            if (wanted.IsMatch(name))
//            {
//                CTask::PostTask(xnew(CTask, func));
//            }
//        }
//    }
//
//    /// \brief 포스트한 태스크 객체들이 완료되기를 기다린다.
//    inline void WaitAll()
//    {
//        while (0 < CTask::GetPendingCount())
//        {
//            Sleep(100);
//        }
//    }
//
//    /// \brief 해당 사항 있는 애셋일 경우, 주어진 함수자를 실행
//    template <typename Functor>
//    inline void Exec(LPCTSTR name, const CAssetNameSet& wanted, const Functor& func)
//    {
//        if (wanted.IsMatch(name))
//        {
//            func();
//        }
//    }
//
//    //------------------------------------------------------------------------------------------------------------------
//}