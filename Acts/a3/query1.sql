-- Find all film_ids of films with minimum length or maximum rental duration (compared to all other films). The returned list of film_ids should be sorted in descending order.

-- Put query for Q1 here
SELECT film_id FROM film WHERE 
length = (SELECT MIN(length) FROM film)
OR
rental_duration = (SELECT MAX(rental_duration) FROM film)
ORDER BY film_id DESC;
