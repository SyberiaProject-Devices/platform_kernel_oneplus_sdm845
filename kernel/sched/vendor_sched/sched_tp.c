/* SPDX-License-Identifier: GPL-2.0 */
#include <linux/module.h>

#include <linux/sched.h>
#include <trace/events/sched.h>
#include <../sched.h>

#define CREATE_TRACE_POINTS
#include "sched_events.h"
#include "systrace.h"

//EXPORT_TRACEPOINT_SYMBOL_GPL(sched_find_best_target);
EXPORT_TRACEPOINT_SYMBOL_GPL(sched_cpu_util);
EXPORT_TRACEPOINT_SYMBOL_GPL(sched_setscheduler_uclamp);
EXPORT_TRACEPOINT_SYMBOL_GPL(sched_find_energy_efficient_cpu);
EXPORT_TRACEPOINT_SYMBOL_GPL(0);

static int sched_tp_init(void)
{
	return 0;
}

static void sched_tp_finish(void)
{
}


module_init(sched_tp_init);
module_exit(sched_tp_finish);

MODULE_LICENSE("GPL");
