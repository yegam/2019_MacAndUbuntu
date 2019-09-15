#1.Grass 타입의 포켓몬의 이름을 사전순으로 출력하세요
select name from Pokemon
where type ='Grass'
order by name;

#2.Brown City나 Rainbow City 출신 트레이너의 이름을 사전순으로 출력하세요
select name from Trainer
where hometown ='Brown city' OR hometown = 'Rainbow City'
order by name;

#3.모든 포켓몬의 type을 중복없이 사전순으로 출력하세요
select Distinct type from Pokemon
order by type;

#4.도시의 이름이 B로 시작하는 모든 도시의 이름을 사전순으로 출력하세요
select name from City
where name LIKE 'B%'
order by name;

#5.이름이 M으로 시작하지 않는 트레이너의 고향을 사전순으로 출력하세요
select hometown from Trainer
where name NOT LIKE 'M%'
order by hometown;

#6.잡힌 포켓몬 중 가장 레벨이 높은 포켓몬의 별명을 사전순으로 출력하세요
select nickname from CatchedPokemon
where level = (select max(level) from CatchedPokemon)
order by nickname;

#7.포켓몬의 이름이 알파벳 모음으로 시작하는 포켓몬의 이름을 사전순으로 출력하세요
select name from Pokemon
where name Like 'a%' OR name Like 'e%' OR name Like 'i%' OR name Like 'o%' OR name Like 'u%'
order by name;

#8.잡힌 포켓몬의 평균 레벨을 출력하세요
select AVG(level) from CatchedPokemon;

#9.Yellow가 잡은 포켓몬의 최대 레벨을 출력하세요
select Max(c.level) from CatchedPokemon c
Join Trainer t ON t.id = c.owner_id And t.name = 'yellow';

#10.트레이너의 고향 이름을 중복없이 사전순으로 출력하세요
select Distinct hometown from Trainer
order by hometown;


#11.닉네임이 A로 시작하는 포켓몬을 잡은 트레이너의 이름과 포켓몬의 닉네임을 트레이너의 이름의 사전순으로 출력하세요
#12.Amazon 특성을 가진 도시의 리더의 트레이너 이름을 출력하세요
#13.불속성 포켓몬을 가장 많이 잡은 트레이너의 id와, 그 트레이너가 잡은 불속성 포켓몬의 수를 출력하세요

#14.포켓몬 ID가 한 자리 수인 포켓몬의 type을 중복 없이 포켓몬 ID의 내림차순으로 출력하세요
#15.포켓몬의 type이 Fire이 아닌 포켓몬의 수를 출력하세요
#16.진화하면 id가 작아지는 포켓몬의 진화 전 이름을 사전순으로 출력하세요
#17.트레이너에게 잡힌 모든 물속성 포켓몬의 평균 레벨을 출력하세요
#18.체육관리더가잡은모든포켓몬중레벨이가장높은포켓몬의별명을출력하세요
#19.Blue city 출신 트레이너들 중 잡은 포켓몬들의 레벨의 평균이 가장 높은 트레이너의 이름을 사전순으로 출력하세요
#20.같은 출신이 없는 트레이너들이 잡은 포켓몬중 진화가 가능하고 Electric 속성을 가진 포켓몬의 이름을 출력하세요
#21.관장들의 이름과 각 관장들이 잡은 포켓몬들의 레벨 합을 레벨 합의 내림차 순으로 출력하세요
#22.가장 트레이너가 많은 고향의 이름을 출력하세요.
#23.Sangnok City 출신 트레이너와 Brown City 출신 트레이너가 공통으로 잡은 포켓몬의 이름을 중복을 제거하여 사전순으로 출력하세요

#24.이름이 P로 시작하는 포켓몬을 잡은 트레이너 중 상록시티출신인 트레이너의 이름을 사전순으로 모두 출력하세요
#25.트레이너의 이름과 그 트레이너가 잡은 포켓몬의 이름을 출력하세요. 트레이너 이름의 사전 순으로 정렬하고, 각 트레이너가 잡은 포켓몬 간에도 사전 순으로 정렬하세요.
#26.2단계 진화만 가능한 포켓몬의 이름을 사전순으로 출력하세요
#27.상록 시티의 관장이 잡은 포켓몬들 중 포켓몬의 타입이 WATER 인 포켓몬의 별명을 사전순으로 출력하세요
#28.트레이너들이 잡은 포켓몬 중 진화한 포켓몬이 3마리 이상인 경우 해당 트레이너의 이름을 사전순으로 출력하세요
#29.어느 트레이너에게도 잡히지 않은 포켓몬의 이름을 사전 순으로 출력하세요
#30.각 출신 도시 별로 트레이너가 잡은 포켓몬 중 가장 레벨이 높은 포켓몬의 레벨을 내림차순으로 출력하세요.
#31.포켓몬 중 3단 진화가 가능한 포켓몬의 ID 와 해당 포켓몬의이름을 1단진화 형태 포켓몬의이름, 2단진화 형태 포켓몬의 이름, 3단 진화 형태 포켓몬의 이름을 ID 의 오름차순으로 출력하세요