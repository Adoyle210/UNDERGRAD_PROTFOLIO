package edu.oregonstate.cs492.assignment4.ui

import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.asLiveData
import androidx.lifecycle.viewModelScope
import edu.oregonstate.cs492.assignment4.data.AppDatabase
import edu.oregonstate.cs492.assignment4.data.BookmarkedCityRepository
import edu.oregonstate.cs492.assignment4.data.CityDatabaseEntry
import kotlinx.coroutines.launch

class BookmarkedCityViewModel (application: Application) : AndroidViewModel(application) {
    private val repo = BookmarkedCityRepository(AppDatabase.getInstance(application).CityDatabaseDao())

    val savedCities = repo.getAllCities().asLiveData()

    fun addBookmarkedCity(city: CityDatabaseEntry) {
        viewModelScope.launch {
            repo.insertBookmarkedCity(city)
        }
    }

    fun removeBookmarkedCity(city: CityDatabaseEntry) {
        viewModelScope.launch {
            repo.deleteBookmarkedCity(city)
        }
    }

    fun nukeBookmarkedCity() {
        viewModelScope.launch {
            repo.nukeBookmarkedCity()
        }
    }
}