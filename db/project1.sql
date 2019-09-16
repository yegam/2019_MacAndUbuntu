#1.Grass 타입의 포켓몬의 이름을 사전순으로 출력하세요
SELECT name FROM Pokemon
WHERE type ='Grass'
ORDER BY name;

#2.Brown City나 Rainbow City 출신 트레이너의 이름을 사전순으로 출력하세요
SELECT name FROM Trainer
WHERE hometown ='Brown city' OR hometown = 'Rainbow City'
ORDER BY name;

#3.모든 포켓몬의 type을 중복없이 사전순으로 출력하세요
SELECT DISTINCT type FROM Pokemon
ORDER BY type;

#4.도시의 이름이 B로 시작하는 모든 도시의 이름을 사전순으로 출력하세요
SELECT name FROM City
WHERE name LIKE 'B%'
ORDER BY name;

#5.이름이 M으로 시작하지 않는 트레이너의 고향을 사전순으로 출력하세요
SELECT hometown FROM Trainer
WHERE name NOT LIKE 'M%'
ORDER BY hometown;

#6.잡힌 포켓몬 중 가장 레벨이 높은 포켓몬의 별명을 사전순으로 출력하세요
SELECT nickname FROM CatchedPokemon
WHERE level = (SELECT MAX(level) FROM CatchedPokemon)
ORDER BY nickname;

#7.포켓몬의 이름이 알파벳 모음으로 시작하는 포켓몬의 이름을 사전순으로 출력하세요
SELECT name FROM Pokemon
WHERE name Like 'a%' 
OR name Like 'e%' 
OR name Like 'i%' 
OR name Like 'o%' 
OR name Like 'u%'
ORDER BY name;

#8.잡힌 포켓몬의 평균 레벨을 출력하세요
SELECT AVG(level) FROM CatchedPokemon;

#9.Yellow가 잡은 포켓몬의 최대 레벨을 출력하세요
SELECT Max(CatchedPokemon.level) 
FROM CatchedPokemon, Trainer
WHERE Trainer.id = CatchedPokemon.owner_id 
And Trainer.name = 'yellow';

#10.트레이너의 고향 이름을 중복없이 사전순으로 출력하세요
SELECT DISTINCT hometown FROM Trainer
ORDER BY hometown;

#11.닉네임이 A로 시작하는 포켓몬을 잡은 트레이너의 이름과 포켓몬의 닉네임을 트레이너의 이름의 사전순으로 출력하세요
SELECT Trainer.name, nickname
FROM CatchedPokemon, Trainer, Pokemon 
WHERE nickname LIKE 'A%' 
AND CatchedPokemon.owner_id = Trainer.id 
AND CatchedPokemon.pid = Pokemon.id
ORDER BY Trainer.name;

#12.Amazon 특성을 가진 도시의 리더의 트레이너 이름을 출력하세요
SELECT Trainer.name
FROM Trainer, City, Gym
WHERE City.description = 'Amazon'
AND Gym.city = City.name
AND Gym.leader_id = Trainer.id;

#//13.불속성 포켓몬을 가장 많이 잡은 트레이너의 id와, 그 트레이너가 잡은 불속성 포켓몬의 수를 출력하세요
SELECT CatchedPokemon.owner_id,count(*)
FROM CatchedPokemon, Pokemon
WHERE CatchedPokemon.pid = Pokemon.id
AND Pokemon.type = 'Fire';

#14.포켓몬 ID가 한 자리 수인 포켓몬의 type을 중복 없이 포켓몬 ID의 내림차순으로 출력하세요
SELECT DISTINCT type FROM Pokemon
WHERE id < 10
ORDER BY id DESC;

#15.포켓몬의 type이 Fire이 아닌 포켓몬의 수를 출력하세요
SELECT count(type) FROM Pokemon
WHERE type != 'Fire';

#16.진화하면 id가 작아지는 포켓몬의 진화 전 이름을 사전순으로 출력하세요


#17.트레이너에게 잡힌 모든 물속성 포켓몬의 평균 레벨을 출력하세요
SELECT AVG(level) 
FROM CatchedPokemon,Pokemon
WHERE CatchedPokemon.pid = Pokemon.id 
AND Pokemon.type = 'Water';

#18.체육관 리더가 잡은 모든 포켓몬 중 레벨이 가장 높은 포켓몬의 별명을 출력하세요
SELECT nickname FROM CatchedPokemon, Gym
WHERE CatchedPokemon.owner_id = Gym.leader_id
And CatchedPokemon.level = (SELECT MAX(level) 
                            FROM CatchedPokemon, Gym
                            WHERE CatchedPokemon.owner_id = Gym.leader_id);

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