package domain

data class RegistrationRecord (
    val courseGroupId: Long,
    var status: RegistrationStatus
) {}