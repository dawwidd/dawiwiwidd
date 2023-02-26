drop table collisions_sf;
drop table collisions;
drop table boroughs_sf;
drop table boroughs;
drop table result;

create external table collisions_sf(street string, zipcode string, person_type string, injured_or_killed string, amount int) ROW FORMAT DELIMITED FIELDS TERMINATED BY '\t' STORED AS TEXTFILE location '${input_dir3}';
create table collisions(street string, zipcode string, person_type string, injured_or_killed string, amount int) STORED AS ORC;
insert overwrite table collisions select * from collisions_sf;

create external table boroughs_sf(zipcode string, borough string) ROW FORMAT DELIMITED FIELDS TERMINATED BY ',' STORED AS TEXTFILE location '${input_dir4}';
create table boroughs(zipcode string, borough string) STORED AS ORC;
insert overwrite table boroughs select * from boroughs_sf;

CREATE TABLE RESULT (street string, person_type string, injured int, killed int) ROW FORMAT SERDE 'org.apache.hadoop.hive.serde2.JsonSerDe' STORED AS TEXTFILE location "${output_dir6}";

INSERT INTO RESULT select c.street as street, c.person_type as person_type, sum(case when c.injured_or_killed='INJURED' then c.amount else 0 end) injured, sum(case when c.injured_or_killed='KILLED' then c.amount else 0 end) killed from collisions c join boroughs b on b.zipcode=c.zipcode where b.borough='MANHATTAN' and c.person_type='PEDESTRIAN' and c.street!='' group by street, person_type ORDER BY injured+killed DESC LIMIT 3;

INSERT INTO RESULT select c.street as street, c.person_type as person_type, sum(case when c.injured_or_killed='INJURED' then c.amount else 0 end) injured, sum(case when c.injured_or_killed='KILLED' then c.amount else 0 end) killed from collisions c join boroughs b on b.zipcode=c.zipcode where b.borough='MANHATTAN' and c.person_type='CYCLIST' and c.street!='' group by street, person_type ORDER BY injured+killed DESC LIMIT 3;

INSERT INTO RESULT select c.street as street, c.person_type as person_type, sum(case when c.injured_or_killed='INJURED' then c.amount else 0 end) injured, sum(case when c.injured_or_killed='KILLED' then c.amount else 0 end) killed from collisions c join boroughs b on b.zipcode=c.zipcode where b.borough='MANHATTAN' and c.person_type='MOTORIST' and c.street!='' group by street, person_type ORDER BY injured+killed DESC LIMIT 3;
