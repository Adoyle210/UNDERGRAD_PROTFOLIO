-- Find the actor_id, first_name, and last_name of all actors who have never been in an Animation film. 
-- Order by the actor_id in ascending order.

-- Put your query for Q4 here

SELECT act.actor_id, act.first_name, act.last_name FROM actor act
    INNER JOIN film_actor fa ON act.actor_id = fa.actor_id
    INNER JOIN film f ON fa.actor_id = f.film_id
    INNER JOIN film_category fc ON f.film_id = fc.film_id
    INNER JOIN category cate ON fc.category_id = cate.category_id
WHERE act.actor_id NOT IN 
    (SELECT act.actor_id FROM actor act
        INNER JOIN film_actor fa ON  act.actor_id=fa.actor_id
        INNER JOIN film f ON fa.film_id=f.film_id
        INNER JOIN film_category fc ON f.film_id=fc.film_id
        INNER JOIN category cate ON fc.category_id=cate.category_id
	WHERE cate.name='Animation'
    GROUP BY act.actor_id)
GROUP BY act.actor_id ASC;