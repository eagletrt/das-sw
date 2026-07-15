#include "acquisinator.h"

#include "eagletrt.h"
#include <stdlib.h>
#include <stdint.h>

/*!
 * \brief Initializes the module
 *
 * \retval ACQUISINATOR_RC_OK if successful
 * \retval ACQUISINATOR_RC_ERROR if fail
 */
enum AcquisinatorReturnCode acquisinator_api_init(void);

/*!
 * \brief  Get the current state of a acquisinator line
 *
 * \param acquisinator The acquisinator to query
 *
 * \retval struct AcquisinatorStrainGauge contains the value of \p acquisinator
 */
struct AcquisinatorStrainGauge acquisinator_api_get_strain_gauge(enum AcquisinatorName acquisinator);

/*!
 * \brief  Set the current state of a acquisinator line
 *
 * \param acquisinator The acquisinator to be set
 * \param first_strain_gauge The value of the first strain guage sensor to set \p acquisinator to
 * \param second_strain_gauge The value of the first strain guage sensor to set \p acquisinator to
 *
 * \retval ACQUISINATOR_RC_OK if successful
 * \retval ACQUISINATOR_RC_ERROR if \p acquisinator are out of bounds
 */
enum AcquisinatorReturnCode acquisinator_api_set_strain_gauge(enum AcquisinatorName acquisinator, struct AcquisinatorStrainGauge strain_gauge);