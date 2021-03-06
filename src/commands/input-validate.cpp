/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <bitcoin/explorer/commands/input-validate.hpp>

#include <iostream>
#include <cstdint>
#include <bitcoin/bitcoin.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;

console_result input_validate::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto index = get_index_option();
    const tx_type& tx = get_transaction_argument();
    const auto& public_key = get_ec_public_key_argument();
    const auto& script = get_prevout_script_argument();
    const auto& signature = get_signature_argument();

    if (index >= tx.inputs.size())
    {
        error << BX_INPUT_VALIDATE_INDEX_OUT_OF_RANGE << std::endl;
        return console_result::failure;
    }

    if (!check_signature(signature, public_key, script, tx, index))
    {
        output << BX_INPUT_VALIDATE_INDEX_INVALID_SIGNATURE << std::endl;
        return console_result::invalid;
    }

    output << BX_INPUT_VALIDATE_INDEX_VALID_SIGNATURE << std::endl;
    return console_result::okay;
}

