-- For each category of film, find the name of the category (as "category_name") and the count of films (as "number_of_films") that MAE HOFFMAN has stared in within that category. 
-- Order by the category name in descending order. 
-- (Note: your query should return every category even if MAE has been in no films in that category--i.e., her count is 0 for "number_of_films" for that respective "category_name").

-- Put query for Q2 here

SELECT cate.name AS category_name, COUNT(act.actor_id) AS number_of_films FROM category cate
    LEFT JOIN film_category AS fc ON cate.category_id=fc.category_id
    LEFT JOIN film AS f ON fc.film_id=f.film_id
    LEFT JOIN film_actor AS fa ON f.film_id=fa.film_id 
    LEFT JOIN actor AS act ON 
        (fa.actor_id=act.actor_id) AND 
        (act.first_name='MAE' AND act.last_name='HOFFMAN')
GROUP BY cate.category_id
ORDER BY cate.name DESC;