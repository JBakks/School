SHOW databases;
USE assign2db;

-- ------------------
-- PART 1 SQL UPDATES
-- ------------------

SELECT * FROM course;
SELECT * FROM courseoffer;
SELECT * FROM hasworkedon;
SELECT * FROM hates;
SELECT * FROM loves;
SELECT * FROM ta;

SELECT * FROM course;
UPDATE course SET coursename = 'Multimedia and Communication' WHERE coursename = 'Multimedia';

SELECT * FROM hasworkedon;
UPDATE hasworkedon SET hours = 200 WHERE tauserid IN (SELECT tauserid FROM ta WHERE firstname LIKE 'R%');

SELECT * FROM course;
SELECT * FROM hasworkedon;

-- ------------------
-- PART 2 SQL INSERTS
-- ------------------

SELECT * FROM course;
INSERT INTO course VALUES ('CS2033', 'Multimedia and Communications2','2', '2003');

SELECT * FROM courseoffer;
INSERT INTO courseoffer VALUES ('RD20', '150', 'Spring', '2022', 'CS2033');
INSERT INTO courseoffer VALUES ('RD21', '170', 'Fall', '2022', 'CS2033');
INSERT INTO courseoffer VALUES ('RD22', '160', 'Fall', '2023', 'CS2033');

SELECT * FROM ta;
INSERT INTO ta VALUES ('tswift', 'Taylor', 'Swift', '251001989', 'PhD');

SELECT * FROM loves;
INSERT INTO loves VALUES ('tswift', 'CS2033');

SELECT * FROM course;
SELECT * FROM courseoffer;
SELECT * FROM ta;
SELECT * FROM loves;

-- -------------------
-- PART 3 SQL QUERIRES
-- -------------------

-- Query 1
SELECT lastname FROM ta;

-- Query 2
SELECT DISTINCT lastname FROM ta;

-- QUERY 3
SELECT * FROM ta ORDER BY firstname;

-- QUERY 4
SELECT firstname, lastname, tauserid FROM ta WHERE degreetype = "Masters";

-- QUERY 5
SELECT coid, term, courseoffer.year, whichcourse FROM courseoffer, course where courseoffer.whichcourse = course.coursenum AND course.coursename like "%Database%";

-- QUERY 6
SELECT * FROM courseoffer, course where courseoffer.whichcourse = course.coursenum AND courseoffer.year < course.year; 

-- QUERY 7

SELECT coursename, lcoursenum FROM course, loves WHERE course.coursenum = loves.lcoursenum AND ltauserid LIKE "%geller%";

-- QUERY 8

SELECT SUM(numstudent) FROM courseoffer WHERE whichcourse = "CS1033";

-- QUERY 9

SELECT DISTINCT firstname, lastname, coursenum FROM hasworkedon, ta, courseoffer, course WHERE ta.tauserid = hasworkedon.tauserid AND hasworkedon.coid = courseoffer.coid AND course.coursenum = courseoffer.whichcourse AND course.level = 1;

-- QUERY 10

-- CREATE VIEW CALCULATING TOTAL HOURS
CREATE VIEW totalhours AS SELECT hasworkedon.tauserid, courseoffer.whichcourse, SUM(hasworkedon.hours) AS totalhours FROM hasworkedon JOIN courseoffer ON hasworkedon.coid = courseoffer.coid GROUP BY hasworkedon.tauserid, courseoffer.whichcourse;

-- CREATE VIEW FOR MAX HOURS PER OFFER
CREATE VIEW maxhoursperoffer AS SELECT whichcourse, MAX(totalhours) AS maxhours FROM totalhours GROUP BY whichcourse;

-- QUERY DATA
SELECT DISTINCT ta.firstname, ta.lastname, totalhours.totalhours AS hours, courseoffer.whichcourse AS course_number FROM totalhours JOIN maxhoursperoffer ON totalhours.whichcourse = maxhoursperoffer.whichcourse AND totalhours.totalhours = maxhoursperoffer.maxhours JOIN ta ON totalhours.tauserid = ta.tauserid JOIN courseoffer ON totalhours.whichcourse = courseoffer.whichcourse;

-- QUERY 11

SELECT lcoursenum AS coursenum FROM loves UNION SELECT hcoursenum AS coursenum FROM hates EXCEPT SELECT c.coursenum FROM course c WHERE c.coursenum IN (SELECT lcoursenum FROM loves UNION SELECT hcoursenum FROM hates);

-- QUERY 12

SELECT lastname, firstname, COUNT(DISTINCT coid) AS numcourseoffering FROM ta JOIN hasworkedon ON ta.tauserid = hasworkedon.tauserid GROUP BY ta.lastname, ta.firstname HAVING COUNT(DISTINCT coid) > 1;

-- QUERY 13

SELECT DISTINCT firstname, lastname, whichcourse AS course_number, coursename AS course_name FROM ta JOIN hasworkedon ON ta.tauserid = hasworkedon.tauserid JOIN courseoffer ON hasworkedon.coid = courseoffer.coid JOIN course ON courseoffer.whichcourse = course.coursenum WHERE ta.tauserid IN (SELECT ltauserid FROM loves WHERE lcoursenum = courseoffer.whichcourse);


-- QUERY 14

-- CREATE VIEW TO COUNT NUMBER OF OCCURANCES

CREATE VIEW fallcourse AS SELECT whichcourse AS coursenum, coursename, COUNT(*) AS count FROM courseoffer JOIN course ON courseoffer.whichcourse = course.coursenum WHERE courseoffer.term = "Fall" GROUP BY courseoffer.whichcourse, course.coursename;

SELECT coursenum, coursename, count FROM fallcourse WHERE count = (SELECT MAX(count) FROM fallcourse);


-- QUERY 15-My QUERY - Find TA with highest total hours across all course offerings

SELECT firstname, lastname, SUM(hours) AS totalhours FROM ta JOIN hasworkedon ON ta.tauserid = hasworkedon.tauserid GROUP BY ta.tauserid ORDER BY totalhours DESC LIMIT 1;

-- ------------------------
-- PART 4 SQL VIEWS/DELETES
-- ------------------------

CREATE VIEW tahatescourse AS SELECT firstname, lastname, ta.tauserid, hcoursenum, coursename FROM ta JOIN hates ON ta.tauserid = hates.htauserid JOIN course ON hates.hcoursenum = course.coursenum ORDER BY level;

SELECT * FROM tahatescourse;

SELECT DISTINCT firstname, lastname, whichcourse FROM tahatescourse JOIN hasworkedon ON tahatescourse.tauserid = hasworkedon.tauserid JOIN courseoffer ON hasworkedon.coid = courseoffer.coid WHERE tahatescourse.hcoursenum = courseoffer.whichcourse;

SELECT * FROM ta;
SELECT * FROM hates;

DELETE FROM ta WHERE tauserid = 'pbing';

SELECT * FROM ta;
SELECT * FROM hates;

DELETE FROM ta WHERE tauserid = 'mgeller';

-- mgeller cannot be deleted because there is a rule in the database that prevents the removal of certain data because its connect to other data. In this case mgeller is a TA on courses in hasworkedon, and those courses cannot be without a TA. pbing was not attached to anyother data so it was okay that she could be deleted.

ALTER TABLE ta ADD image VARCHAR(200);

SELECT * FROM ta;

UPDATE ta SET image = 'https://i.pinimg.com/originals/bf/85/8d/bf858d262ce992754e2b78042c9e0fe8.gif' WHERE tauserid = 'mgeller';

SELECT * FROM ta;



