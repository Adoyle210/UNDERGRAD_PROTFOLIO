-- Find the title (as "film_title") of all films which feature both RALPH CRUZ and WILL WILSON. 
-- Order the results by film_title in ascending order.

-- Put your query for Q5 here.
(SELECT f.title AS film_title FROM film f
    INNER JOIN film_actor fa1 ON f.film_id=fa1.film_id
    INNER JOIN actor act1 ON fa1.actor_id=act1.actor_id
    INNER JOIN film_actor fa ON f.film_id=fa.film_id
    INNER JOIN actor act ON fa.actor_id=act.actor_id
WHERE (act.first_name='RALPH' AND act.last_name='CRUZ')
    AND (act1.first_name='WILL' AND act1.last_name='WILSON'))
ORDER BY f.title;
 