Base 프로젝트

개요
프로젝트에 사용할 가장 기본적인 도구들의 최상위 클래스를 모아놓은 프로젝트

본문

1. ECS (https://m.blog.naver.com/kiseop91/221855589754)
	프로젝트에서 사용할 도구조합의 최상위 개념

	
		System - 기능의 관리자 보통 싱글톤일듯, 기능 함수들
		Entity - 기능을 담당하는 객체 - 변수와 기능 함수들
		Conmponent -  기능을 어떻게 핸들링할지 정의함 - 보통 기능함수들
			
	도구 사용 흐름
		System에서 Entity의 Component를 찾아서 기능 함수 호출
		Component에서는 Entity의 멤버를 참조해서 기능 수행

2. 수학

3. 시간

4. 뭐 등등
