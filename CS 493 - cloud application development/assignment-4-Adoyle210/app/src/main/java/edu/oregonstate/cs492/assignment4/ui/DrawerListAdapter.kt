package edu.oregonstate.cs492.assignment4.ui

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import edu.oregonstate.cs492.assignment4.R
import edu.oregonstate.cs492.assignment4.data.CityDatabaseEntry

class DrawerListAdapter(private val onDrawerClick: (CityDatabaseEntry) -> Unit)
    : RecyclerView.Adapter<DrawerListAdapter.ViewHolder>() {
    var cityList = listOf<CityDatabaseEntry>()

    fun updateCityList(newCityList: List<CityDatabaseEntry>?) {
        cityList = newCityList ?: listOf()
        notifyDataSetChanged()
    }

    override fun getItemCount() = cityList.size

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val itemView = LayoutInflater.from(parent.context)
            .inflate(R.layout.drawer_list_item, parent, false)
        return ViewHolder(itemView, onDrawerClick)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        holder.bind(cityList[position])
    }

    class ViewHolder(itemView: View, val onClick: (CityDatabaseEntry) -> Unit)
        : RecyclerView.ViewHolder(itemView) {
        private val nameTV: TextView = itemView.findViewById(R.id.tv_bookmarked_city)
        private var currentCityDatabaseEntry: CityDatabaseEntry? = null

        init {
            itemView.setOnClickListener {
                currentCityDatabaseEntry?.let(onClick)
            }
        }

        fun bind(cityDatabaseEntry: CityDatabaseEntry) {
            currentCityDatabaseEntry = cityDatabaseEntry
            nameTV.text = cityDatabaseEntry.savedCity
        }
    }

}