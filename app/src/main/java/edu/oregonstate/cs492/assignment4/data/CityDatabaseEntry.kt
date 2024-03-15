package edu.oregonstate.cs492.assignment4.data

import androidx.room.Entity
import androidx.room.PrimaryKey
import java.io.Serializable

@Entity
data class CityDatabaseEntry (
    @PrimaryKey
    val savedCity: String,
    val timeStamp: Int
) : Serializable