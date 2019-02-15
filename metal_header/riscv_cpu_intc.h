/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef __METAL_HEADER_RISCV_CPU_INTC__H
#define __METAL_HEADER_RISCV_CPU_INTC__H

#include "metal_header/device.h"

#include <regex>

class riscv_cpu_intc : public Device {
  public:
    riscv_cpu_intc(std::ostream &os, const fdt &dtb)
      : Device(os, dtb, "riscv,cpu-intc")
    {}

    void declare_structs()
    {
      dtb.match(
	std::regex(compat_string),
	[&](node n) {
	  emit_struct_decl("riscv_cpu_intc_data", n, "_data");
	  emit_const_struct_decl("riscv_cpu_intc", n);
	}
      );
    }

    void define_structs()
    {
      dtb.match(
	std::regex(compat_string),
	[&](node n) {
	  emit_struct_begin("riscv_cpu_intc_data", n, "_data");
	  emit_struct_field("init_done", "0");
	  emit_struct_end();

	  emit_const_struct_begin("riscv_cpu_intc", n);

	  emit_struct_field("vtable", "&__metal_driver_vtable_riscv_cpu_intc");
	  emit_struct_field("controller.vtable", "&__metal_driver_vtable_riscv_cpu_intc.controller_vtable");

	  emit_struct_field("data", "&__metal_dt_" + n.handle() + "_data");

	  if (n.field_exists("interrupt-controller")) {
	    emit_struct_field("interrupt_controller", "1");
	  }

	  emit_struct_end();
	});
    }

    void create_handles()
    {
      dtb.match(
	std::regex(compat_string),
	[&](node n) {
	  emit_def_handle("__METAL_DT_RISCV_CPU_INTC_HANDLE", n, ".controller");
      });
    }
};

#endif
