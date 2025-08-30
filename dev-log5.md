# [DevLog #5] 하드코딩 고치기 (7일차 정리)

## 작성일: 2025-08-30

---

### 하드코딩이란?

프로그램 소스코드에 데이터를 직접 입력하는 방식
-> 숫자나 문자열같은 특정 값을 변수나 상수로 선언하지 않고 코드에 박아 넣는 것

문제점 
-> 낮은 가독성, 유지보수의 어려움, 낮은 확장성

ex)
[5일차 코드 中]
```
void levelUp(int e){
    // ...
    maxExp += maxExp / 10;
    hp += hp / 5;
    maxHp += maxHp / 5;
    attack += attack / 5;
    defense += defense / 5;
}
```
[변경 후]
```
const float STAT_GROWTH_RATE=0.2f;
const float EXP_GROWTH_RATE=0.1f;
void levelUp(int e){
		exp+=e;
		while (exp >= maxExp) {
			// ...
			maxExp += maxExp*EXP_GROWTH_RATE;
			hp += hp * STAT_GROWTH_RATE;
			maxHp += maxHp *STAT_GROWTH_RATE;
			attack += attack * STAT_GROWTH_RATE;
			defense += defense * STAT_GROWTH_RATE;
		}
	}
```
---

### 느낀 점

더 멋진 프로젝트를 위해서 하드코딩에 대해서 알아보았다... 코드 가독성, 확장성, 유지보수를 위해서 필요한 첫번째 절차인것 같다.
앞으로 코딩할때 하드코딩을 피하는 습관을 들이도록 해야겠다.
