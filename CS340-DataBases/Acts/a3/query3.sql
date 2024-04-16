-- For each actor, find the actor_id, first_name, last_name and total_combined_film_length of "Animation" films for that actor.
-- Order your results by the actor_id in ascending order. 
-- (Note: actors who have not stared in any animation films would have a total_combined_film_length of 0).

-- Put query for Q3 here

SELECT act.actor_id, act.first_name, act.last_name, IFNULL(Anima.sum,0) AS total_combined_film_length FROM actor act
LEFT JOIN
    (SELECT act.actor_id AS actor_id, SUM(f.length) AS sum FROM actor act
        INNER JOIN film_actor fa ON act.actor_id=fa.actor_id
        INNER JOIN film f ON fa.film_id=f.film_id
        INNER JOIN film_category fc ON f.film_id=fc.film_id
        INNER JOIN category cate ON fc.category_id=cate.category_id
    WHERE cate.name='Animation'
    GROUP BY act.actor_id
    ORDER BY sum ASC) AS Anima ON act.actor_id=Anima.actor_id
ORDER BY act.actor_id ASC;
