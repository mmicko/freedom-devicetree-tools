/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef __METAL_HEADER_SIFIVE_HTIF0__H
#define __METAL_HEADER_SIFIVE_HTIF0__H

#include "metal_header/device.h"

#include <regex>

class sifive_htif0 : public Device {
  public:
    sifive_htif0(std::ostream &os, const fdt &dtb)
      : Device(os, dtb, "sifive,htif0")
    {}

    void include_headers()
    {
      dtb.match(
	std::regex(compat_string),
	[&](node n) {
	  emit_include(compat_string);
	});
    }

    void declare_structs()
    {
      dtb.match(
	std::regex(compat_string),
	[&](node n) {
	  emit_struct_decl("sifive_htif0", "shutdown", n);
	  emit_struct_decl("sifive_htif0", "uart", n);
	}
      );
    }

    void define_structs()
    {
      dtb.match(
	std::regex(compat_string),
	[&](node n) {
	  emit_struct_begin("sifive_htif0", "shutdown", n);
	  emit_struct_field("vtable", "&__metal_driver_vtable_sifive_htif0_shutdown");
	  emit_struct_field("shutdown.vtable", "&__metal_driver_vtable_sifive_htif0_shutdown.shutdown");
	  emit_struct_end();

	  emit_struct_begin("sifive_htif0", "uart", n);
	  emit_struct_field("vtable", "&__metal_driver_vtable_sifive_htif0_uart");
	  emit_struct_field("uart.vtable", "&__metal_driver_vtable_sifive_htif0_uart.uart");
	  emit_struct_end();
	});
    }

    void create_handles()
    {
      dtb.match(
	std::regex(compat_string),
	[&](node n) {
	  emit_def_handle("__METAL_DT_SHUTDOWN_HANDLE", "shutdown", n, ".shutdown");
	  emit_def_handle("__METAL_DT_STDOUT_UART_HANDLE", "uart", n, ".uart");
	});
    }
};

#endif
