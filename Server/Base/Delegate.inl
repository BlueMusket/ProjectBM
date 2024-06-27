#define __WIDEN2__(x) L ## x
#define __WIDEN__(x) __WIDEN2__(x)

#ifndef __WFILE__
#   define __WFILE__ __WIDEN__(__FILE__)
#endif

#ifndef __WFUNCTION__
#   define __WFUNCTION__ __WIDEN__(__FUNCTION__)
#endif

#define DELEGATE_NANE(X) CDelegate_

namespace Delegate
{

#define CDELEGATE DELEGATE_NANE(X)##DELEGATE_ARGS_COUNT

	class CDELEGATE
	{
	public:
		DELEGATE_TEMPLATE_ARGS
		static CDELEGATE Clone(DELEGATE_ARGS)
		{
			CDELEGATE delegate;

			return delegate;
		}
	};

#undef CDELEGATE
}