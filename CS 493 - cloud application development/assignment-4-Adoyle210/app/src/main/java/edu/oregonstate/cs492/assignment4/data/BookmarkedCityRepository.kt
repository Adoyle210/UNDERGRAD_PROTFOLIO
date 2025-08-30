package edu.oregonstate.cs492.assignment4.data

class BookmarkedCityRepository (private val dao: CityDatabaseDao) {
    suspend fun insertBookmarkedCity(city: CityDatabaseEntry) = dao.insert(city)
    suspend fun deleteBookmarkedCity(city: CityDatabaseEntry) = dao.delete(city)
    suspend fun nukeBookmarkedCity() = dao.nukeTable()
    fun getAllCities() = dao.getAllCities()
}