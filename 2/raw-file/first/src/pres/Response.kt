package pres

data class Response<T>(
    val success: Boolean,
    val message: String,
    val data: T? = null
)